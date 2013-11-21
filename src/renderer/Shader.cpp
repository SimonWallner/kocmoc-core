#include <kocmoc-core/renderer/Shader.hpp>

#include <fstream>
#include <cassert>

#include <kocmoc-core/renderer/RenderMesh.hpp>
#include <kocmoc-core/renderer/constants.hpp>
#include <kocmoc-core/util/util.hpp>
#include <kocmoc-core/resources/ResourceManager.hpp>

#include <objectif-lune/Singleton.hpp>


using namespace kocmoc::core::renderer;

using std::string;

Shader::Shader(const std::string &_vertexShaderName,
			   const std::string &_fragmentShaderName,
			   const resources::ResourceManager* _resourceManager)
	: prepared(false)
	, primed(false)
	, vertexShaderName(_vertexShaderName)
	, fragmentShaderName(_fragmentShaderName)
	, resourceManager(_resourceManager)
{}

bool Shader::prepare()
{
	if (prepared)
		destroy();

	string vertexShaderSource = resourceManager->preprocessShader(vertexShaderName);
	string fragmentShaderSource = resourceManager->preprocessShader(fragmentShaderName);

	vertexShader = compile(GL_VERTEX_SHADER, vertexShaderSource, vertexShaderName);
	fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentShaderSource, fragmentShaderName);
	link();
	
	// set texture sampler uniforms
	bind();
	{
		GLint location;
		location = getUniformLocation("sDiffuse");
		if (location >= 0)
			glUniform1i(location, textureUnitDiffuse);
		location = getUniformLocation("sSpecular");
		if (location >= 0)
			glUniform1i(location, textureUnitSpecular);
		location = getUniformLocation("sGloss");
		if (location >= 0)
			glUniform1i(location, textureUnitGloss);
		location = getUniformLocation("sNormal");
		if (location >= 0)
			glUniform1i(location, textureUnitNormal);
	}
	unbind();

	prepared = true;
	return prepared;
}

Shader::~Shader()
{
	destroy();
}

void Shader::reload()
{
	if(prepared)
	{
		objectifLune::Singleton::Get()->debug("--- reloading shader: '"
											 + vertexShaderName
											 + "', '" + fragmentShaderName
											 + "'");
		destroy();
		prepare();
	}
}

void Shader::destroy()
{
	if (prepared)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(programHandle);
	}

	prepared = false;
	primed = false;
}

GLuint Shader::compile(GLenum type, const std::string &source, const std::string name)
{
	// Create shader object
	const GLuint shaderHandle = glCreateShader(type);

	if (shaderHandle == 0) {
		objectifLune::Singleton::Get()->warn("Could not create shader object.");
		return 0;
	}

	const char* src = source.c_str();
	const int len = source.size();
	glShaderSource(shaderHandle, 1, &src, &len);
	glCompileShader(shaderHandle);

	// Check for errors
	int status;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		objectifLune::Singleton::Get()->warn("Shader compilation failed: '"
											 + name + "'");
		dumpShaderLog(shaderHandle);
		objectifLune::Singleton::Get()->trace(source);
	}

	return shaderHandle;    
}

void Shader::link(void)
{
	// Create program handle
	programHandle = glCreateProgram();

	// Attach shaders
	glAttachShader(programHandle, vertexShader);
	glAttachShader(programHandle, fragmentShader);

	// bind attribute locations to indexes
	glBindAttribLocation(programHandle, vertexAttributePositionIndex, vertexAttributePositionName);
	glBindAttribLocation(programHandle, vertexAttributeNormalIndex, vertexAttributeNormalName);
	glBindAttribLocation(programHandle, vertexAttributeUVIndex, vertexAttributeUVName);
	glBindAttribLocation(programHandle, vertexAttributeTangentIndex, vertexAttributeTangentName);
	glBindAttribLocation(programHandle, vertexAttributeColorIndex, vertexAttributeColorName);
		
	glLinkProgram(programHandle);

	// Check for problems
	int status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		objectifLune::Singleton::Get()->warn("Shader linking failed.");
		dumpProgramLog(programHandle);

		glDeleteProgram(programHandle);
		programHandle = 0;
	}
}

void Shader::dumpProgramLog(GLuint programHandle) const
{
	char logBuffer[LOG_BUFFER_SIZE];
	GLsizei length;

	logBuffer[0] = '\0';
	glGetProgramInfoLog(programHandle, LOG_BUFFER_SIZE, &length,logBuffer);

	if (length > 0) {
		objectifLune::Singleton::Get()->debug(logBuffer);
	}
}

void Shader::dumpShaderLog(GLuint shader) const
{
	char logBuffer[LOG_BUFFER_SIZE];
	GLsizei length;

	logBuffer[0] = '\0';
	glGetShaderInfoLog(shader, LOG_BUFFER_SIZE, &length,logBuffer);

	if (length > 0) {
		objectifLune::Singleton::Get()->debug(logBuffer);
	}
}

void Shader::bind() const
{
	//assert(isUploaded);
	glUseProgram(programHandle);
}

void Shader::unbind() const
{
	//assert(isUploaded);
	glUseProgram(0);
}

GLint Shader::getUniformLocation(const std::string &name) const
{
	return glGetUniformLocation(programHandle, name.c_str());
}
