#include <kocmoc-core/renderer/Shader.hpp>

#include <fstream>
#include <iostream>
#include <cassert>

using namespace kocmoc::core::renderer;

using std::string;
using std::cerr;
using std::cout;
using std::endl;

Shader::Shader(const std::string &_vertexShaderName, const std::string &_fragmentShaderName)
	: prepared(false)
	, vertexShaderName(_vertexShaderName)
	, fragmentShaderName(_fragmentShaderName)
{}

bool Shader::prepare()
{
	if (prepared)
		destroy();

	// Load the shader files
	string vertexShaderSource;
	string fragmentShaderSource;
//
//	try 
//	{
//		vertexShaderSource = util::parser::parseShader(vertexShaderName, pathPrefix);
//	}
//	catch (Exception& e)
//	{
//		cerr << "Vertex shader " << vertexShaderName <<" failed to parse. Cause:" << endl;
//		cerr << e.getMessage() << endl;
//		return false;
//	}
//
//	try 
//	{
//		fragmentShaderSource = util::parser::parseShader(fragmentShaderName, pathPrefix);
//	}
//	catch (Exception& e)
//	{
//		cerr << "Fragment shader " << fragmentShaderName <<" failed to parse. Cause:" << endl;
//		cerr << e.getMessage() << endl;
//		return false;
//	}
//
//
//	// Compile the shaders
//	vertexShader = compile(GL_VERTEX_SHADER, vertexShaderSource);
//	if (vertexShader == 0)
//		return false;
//
//	fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentShaderSource);
//	if (fragmentShader == 0)
//		return false;
//
//	// Link the shaders into a program
//	link();
//	if (programHandle == 0)
//		return false;

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
		std::cout << "--- reloading shader: [" << vertexShaderName << "/" << fragmentShaderName << "]" << std::endl;
		destroy();
		prepare();
	}
}

void Shader::destroy()
{
	if (prepared)
	{
		glDeleteProgram(programHandle);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	prepared = false;
}

GLuint Shader::compile (GLenum type, const std::string &source)
{
	// Create shader object

	GLuint shaderHandle = glCreateShader(type);

	if (shaderHandle == 0) {
		cerr << "Could not create shader object." << endl;
		return 0;
	}

	// Define shader source and compile

	const char* src = source.data();
	int len = source.size();

	glShaderSource(shaderHandle, 1, &src, &len);

	glCompileShader(shaderHandle);

	// Check for errors
	int status;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Shader compilation failed: (" << vertexShaderName << ", "
			 << fragmentShaderName << ")" << endl;
		shaderLog(shaderHandle);
	}

	return shaderHandle;    
}

void Shader::link(void)
{
	// Create program handle
	programHandle = glCreateProgram();

	// Attach shaders and link
	glAttachShader(programHandle, vertexShader);
	glAttachShader(programHandle, fragmentShader);

//	// bind attribute and frag data locations to indexes
//	for (VertexAttributeSemanticList::const_iterator ci = vertexAttributeSemanticList.begin();
//		ci != vertexAttributeSemanticList.end();
//		ci++)
//	{
//		glBindAttribLocation(programHandle, ci->attributeLocation, ci->attributeShaderName.c_str());
//	}
//	glBindFragDataLocation(programHandle, 0, FRAGMENT_DATA_LOCATION_0_NAME);
//	glBindFragDataLocation(programHandle, 1, FRAGMENT_DATA_LOCATION_1_NAME);


	glLinkProgram(programHandle);

	// Check for problems
	int status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Shader linking failed." << endl;
		programLog(programHandle);

		glDeleteProgram(programHandle);
		programHandle = 0;
	}
}

#define LOG_BUFFER_SIZE 8096

void Shader::programLog(GLuint programHandle)
{
	char logBuffer[LOG_BUFFER_SIZE];
	GLsizei length;

	logBuffer[0] = '\0';
	glGetProgramInfoLog(programHandle, LOG_BUFFER_SIZE, &length,logBuffer);

	if (length > 0) {
		cout << logBuffer << endl;
	}
}

void Shader::shaderLog(GLuint shader)
{
	char logBuffer[LOG_BUFFER_SIZE];
	GLsizei length;

	logBuffer[0] = '\0';
	glGetShaderInfoLog(shader, LOG_BUFFER_SIZE, &length,logBuffer);

	if (length > 0) {
		cout << logBuffer << endl;
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

GLint Shader::getAttributeLocation(const std::string &name) const
{
	//assert(isUploaded);
	return glGetAttribLocation(programHandle, name.c_str());
}

GLint Shader::getUniformLocation(const std::string &name) const
{
	//assert(isUploaded);
	GLint location = glGetUniformLocation(programHandle, name.c_str());
	//if (location < 0 && _DEBUG)
	//	cout << "uniform location: " << name << " not found!" << endl;
	return location;
}