#include "OpenGLShader.h"

#include <fstream>
#include <sstream>
#include <string>

OpenGLShader::OpenGLShader()
{
}

OpenGLShader::~OpenGLShader()
{
	if (ShaderID != 0)
	{
		glDeleteShader(ShaderID);
	}
}

std::string OpenGLShader::Load(const std::string & path)
{
	GLenum type;
	if (path.find(".vert") != std::string::npos)
	{
		type = GL_VERTEX_SHADER;
	}
	else if (path.find(".frag") != std::string::npos)
	{
		type = GL_FRAGMENT_SHADER;
	}
	else
		return "Unrecognized extensions. Only .vert & .frag are accepted";

	ShaderID = glCreateShader(type);

	if (ShaderID == 0)
		return "Failed to create shader";

	std::ifstream file(path);

	if (!file.is_open())
		return "File doesn't exist";

	std::stringstream shader;
	shader << file.rdbuf();
	
	std::string shaderStr = shader.str();
	int size = shaderStr.size();
	glShaderSource(ShaderID, 1, (GLchar**)shaderStr.c_str(), &size);

	glCompileShader(ShaderID);

	GLint result;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		GLint logLength;
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &logLength);

		char * message = new char[logLength + 1];
		glGetShaderInfoLog(ShaderID, logLength, NULL, message);
		std::string ret = message;

		delete[] message;
		return ret;
	}
	
	return "";

}