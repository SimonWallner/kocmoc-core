#include <kocmoc-core/renderer/FrameBuffer21.hpp>

#include <kocmoc-core/math/math.hpp>
#include <kocmoc-core/renderer/Shader.hpp>

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
							 util::Properties* props, const resources::ResourceManager* _resourceManager)
	: frameWidth(_frameWidth * 2)
	, frameHeight(_frameHeight * 2)
	, gateWidth(_gateWidth * 2)
	, gateHeight(_gateHeight * 2)
//	: frameWidth(_frameWidth)
//	, frameHeight(_frameHeight)
//	, gateWidth(_gateWidth)
//	, gateHeight(_gateHeight)
	, windowWidth(_windowWidth)
	, windowHeight(_windowHeight)
	, angleOfView(_angleOfView)
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, frameWidth, frameHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

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

	GLfloat topX = -(float)(gateWidth / 2) / windowWidth;
	GLfloat topY = (float)(gateHeight / 2) / windowHeight;
	GLfloat bottomX = (float)(gateWidth / 2) / windowWidth;
	GLfloat bottomY = -(float)(gateHeight / 2) / windowHeight;
	
//	GLfloat topX = -(float)(gateWidth) / windowWidth;
//	GLfloat topY = (float)(gateHeight) / windowHeight;
//	GLfloat bottomX = (float)(gateWidth) / windowWidth;
//	GLfloat bottomY = -(float)(gateHeight) / windowHeight;

	float horizontalScale = (float)gateWidth / frameWidth;
	float horizontalOffset = (1 - horizontalScale) / 2.0f;
	float verticalScale = (float)gateHeight / frameHeight;
	float verticallOffset = (1 - verticalScale) / 2.0f;

//	unsigned int indices[] = {0, 3, 2, 1, 0, 2};
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
	
	GLfloat* data = new GLfloat[averageWidth * averageHeight * 4];
	glGetTexImage(GL_TEXTURE_2D, maxMipLevel - 2, GL_RGBA, GL_FLOAT, data);
	
	GLfloat averageLuminance = 0;
	for (int i = 0; i < (averageWidth * averageHeight); i++)
	{
		averageLuminance += data[i*4];		// r
		averageLuminance += data[i*4 + 1];	// g
		averageLuminance += data[i*4 + 2];	// b
	}
	averageLuminance /= (averageWidth * averageHeight);
	objectifLune::Singleton::Get()->scalar("log lum", averageLuminance);
	
	// enforce hard boarders to compensate +- INF fuck-up.
	averageLuminance = min<float>(max<float>(0.001f, averageLuminance), 10);

	
	if (!shader->isPrimed())
	{
		shader->bind();
		{
			GLint location;
			
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
			glUniform1f(location, averageLuminance);
		
		renderMesh->draw(NULL, glm::mat4(1));
	}
	shader->unbind();
}


void FrameBuffer21::setFBOTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
}
