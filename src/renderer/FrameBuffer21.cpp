#include <kocmoc-core/renderer/FrameBuffer21.hpp>

#include <kocmoc-core/math/math.hpp>
#include <kocmoc-core/renderer/Shader.hpp>
#include <kocmoc-core/util/util.hpp>
#include <kocmoc-core/scene/ImageLoader.hpp>

#include <kocmoc-core/resources/ResourceManager.hpp>

#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core::renderer;
using namespace kocmoc::core::scene;

using kocmoc::core::math::sign;
using kocmoc::core::math::min;
using kocmoc::core::math::max;

FrameBuffer21::FrameBuffer21(int _frameWidth, int _frameHeight, int _gateWidth, int _gateHeight,
							 int _windowWidth, int _windowHeight,
							 float _angleOfView,
							 util::Properties* props, const resources::ResourceManager* _resourceManager,
							 float _supersample)
	: frameWidth(_frameWidth * _supersample)
	, frameHeight(_frameHeight * _supersample)
	, gateWidth(_gateWidth * _supersample)
	, gateHeight(_gateHeight * _supersample)
	, windowWidth(_windowWidth)
	, windowHeight(_windowHeight)
	, angleOfView(_angleOfView)
	, supersample(_supersample)
	, resourceManager(_resourceManager)
{
	// generate flaot fbo
	glGenFramebuffers(1, &fboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

	// create a depth-buffer
	glGenRenderbuffers(1, &depthbufferHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, depthbufferHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth, frameHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbufferHandle);

	// create and bind colour texture
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, frameWidth, frameHeight, 0, GL_RGBA, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glGenerateMipmap(GL_TEXTURE_2D);
	maxMipLevel = (unsigned int)(log(float(((frameWidth > frameHeight) ? frameWidth : frameHeight))) / log(2.0f));
	glGetTexLevelParameteriv(GL_TEXTURE_2D, maxMipLevel - 2, GL_TEXTURE_WIDTH, &averageWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, maxMipLevel - 2, GL_TEXTURE_HEIGHT, &averageHeight);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureHandle, 0);
	
	check();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	setupShader(props);
	createQuad();
	
	lutHandle = resourceManager->loadImage3D("LUT32.png", false);
}

void FrameBuffer21::check()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		switch(status) {
			case GL_FRAMEBUFFER_UNSUPPORTED:
				objectifLune::Singleton::Get()->error("Unsupported framebuffer format");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				objectifLune::Singleton::Get()->error("Framebuffer incomplete, missing attachment");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				objectifLune::Singleton::Get()->error("Framebuffer incomplete, missing draw buffer");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				objectifLune::Singleton::Get()->error("Framebuffer incomplete, missing read buffer");
				break;
			default:
				objectifLune::Singleton::Get()->error("Unknown Framebuffer error");
				break;
		}
	}
}

void FrameBuffer21::createQuad()
{
	// TODO: migrate to renderMesh
	GLfloat topX = -(float)(gateWidth / supersample) / windowWidth;
	GLfloat topY = (float)(gateHeight / supersample) / windowHeight;
	GLfloat bottomX = (float)(gateWidth / supersample) / windowWidth;
	GLfloat bottomY = -(float)(gateHeight / supersample) / windowHeight;

	float horizontalScale = (float)gateWidth / frameWidth;
	float horizontalOffset = (1 - horizontalScale) / 2.0f;
	float verticalScale = (float)gateHeight / frameHeight;
	float verticallOffset = (1 - verticalScale) / 2.0f;

	unsigned int indices[] = {0, 1, 2, 0, 2, 3};
	
	GLfloat quadVertices[] = {bottomX,  bottomY, -0.5f,
		bottomX, topY, -0.5f,
		topX, topY, -0.5f,
		topX, bottomY, -0.5f};

	GLfloat quadTexCoord[] = {	horizontalScale + horizontalOffset,	verticallOffset,
								horizontalScale + horizontalOffset,	verticalScale + verticallOffset,
								horizontalOffset,					verticalScale + verticallOffset,
								horizontalOffset,					verticallOffset};

	
	TriangleMesh* triMesh = new TriangleMesh(6, indices, 4,
											 quadVertices, NULL, quadTexCoord);
	renderMesh = new RenderMesh21(triMesh, shader);
	renderMesh->prepare();
}

void FrameBuffer21::setupShader(util::Properties* props)
{
	std::string mediaPath = props->getString(types::symbolize("core-media-path"));
	shader = resourceManager->getShader("post.vert", "post.frag");

	shader->prepare();
}


void FrameBuffer21::drawFBO()
{
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	// compute average luminance
	unsigned int pixels = averageWidth * averageHeight;
	GLfloat* data = new GLfloat[pixels * 4];
	glGetTexImage(GL_TEXTURE_2D, maxMipLevel - 2, GL_RGBA, GL_FLOAT, data);
	
	float logLum = 0.0f;
	for (unsigned int i = 0; i < pixels; i++)
	{
		logLum += util::logLuminance(data[i*4], data[i*4 + 1], data[i*4 + 2]);
	}
	logLum /= (float) pixels;
	
	objectifLune::Singleton::Get()->scalar("log lum", logLum);
	
	// enforce hard boarders to compensate +- INF fuck-up.
	// Also cap the low and high end.
	logLum = min<float>(max<float>(0.0f, logLum), 10.0f);

	
	if (!shader->isPrimed())
	{
		shader->bind();
		{
			GLint location;
			if ((location = shader->getUniformLocation("sColourLUT")) >= 0)
				glUniform1i(location, 1);
			
			if ((location = shader->getUniformLocation("dimension")) >= 0)
				glUniform2i(location, gateWidth, gateHeight);
			
			if ((location = shader->getUniformLocation("angleOfView")) >= 0)
				glUniform1f(location, angleOfView);
		}
		shader->unbind();
		shader->markPrimed();
	}

	setFBOTexture();
	shader->bind();
	{
		GLint location;
		if ((location = shader->getUniformLocation("averageLuminance")) >= 0)
			glUniform1f(location, logLum);
		
		renderMesh->draw(NULL, glm::mat4(1));
	}
	shader->unbind();
}


void FrameBuffer21::setFBOTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_3D, lutHandle);
}
