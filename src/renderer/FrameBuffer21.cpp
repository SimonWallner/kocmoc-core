#include <kocmoc-core/renderer/FrameBuffer21.hpp>

#include <iostream>

#include <kocmoc-core/math/math.hpp>
#include <kocmoc-core/renderer/Shader.hpp>

using namespace kocmoc::core::renderer;
using namespace kocmoc::core::scene;

using std::cout;
using std::endl;
using kocmoc::core::math::sign;
using kocmoc::core::math::min;
using kocmoc::core::math::max;

FrameBuffer21::FrameBuffer21(int _frameWidth, int _frameHeight, int _gateWidth, int _gateHeight,
							 int _windowWidth, int _windowHeight,
							 float _angleOfView,
							 util::Properties* props)
	: frameWidth(_frameWidth * 2)
	, frameHeight(_frameHeight * 2)
	, gateWidth(_gateWidth * 2)
	, gateHeight(_gateHeight * 2)
	, windowWidth(_windowWidth)
	, windowHeight(_windowHeight)
	, angleOfView(_angleOfView)
{
	// generate fbo
	glGenFramebuffers(1, &fboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

	// create a depth-buffer
	glGenRenderbuffers(1, &depthbufferHandle);
	glBindRenderbuffer(GL_RENDERBUFFER, depthbufferHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth, frameHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbufferHandle);

	// create and bind texture
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth, frameHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
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
				cout<<"Unsupported framebuffer format"<<endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				cout<<"Framebuffer incomplete, missing attachment"<<endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				cout<<"Framebuffer incomplete, missing draw buffer"<<endl;
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				cout<<"Framebuffer incomplete, missing read buffer"<<endl;
				break;
			default:
				cout<<"Unknown Framebuffer error"<<endl;
				break;
		}
	}
	else{
		cout<<"done"<<endl;
	}
}

void FrameBuffer21::createQuad()
{
	// TODO: migrate to renderMesh

	GLfloat topX = -(float)(gateWidth / 2) / windowWidth;
	GLfloat topY = (float)(gateHeight / 2) / windowHeight;
	GLfloat bottomX = (float)(gateWidth / 2) / windowWidth;
	GLfloat bottomY = -(float)(gateHeight / 2) / windowHeight;

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
	shader = new Shader(mediaPath + "shaders/post.vert", mediaPath + "shaders/post.frag");

	shader->prepare();

	shader->bind();
	{
		GLint location;
		
		if ((location = shader->getUniformLocation("dimension")) >= 0)
			glUniform2i(location, gateWidth, gateHeight);

		if ((location = shader->getUniformLocation("angleOfView")) >= 0)
			glUniform1f(location, angleOfView);

	}
	shader->unbind();
}


void FrameBuffer21::drawFBO()
{
	shader->bind();
	setFBOTexture();
	renderMesh->draw(NULL, glm::mat4(1));

	shader->unbind();
}


void FrameBuffer21::setFBOTexture()
{
	if(textureHandle != 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
	}
}
