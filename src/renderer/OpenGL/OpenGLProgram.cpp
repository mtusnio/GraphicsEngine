#include "OpenGLProgram.h"

OpenGLProgram::OpenGLProgram()
{
	m_ProgramID = 0;
}

OpenGLProgram::~OpenGLProgram()
{
	FreeProgram();
}

void OpenGLProgram::Load(const std::shared_ptr<const OpenGLShader> & vertexShader, const std::shared_ptr<const OpenGLShader> & pixelShader)
{
	_ASSERT(vertexShader.get() != nullptr && pixelShader.get() != nullptr);

	m_VertexShader = vertexShader;
	m_FragmentShader = pixelShader;

	if (m_ProgramID == 0)
		m_ProgramID = glCreateProgram();

	glAttachShader(m_ProgramID, m_VertexShader->ShaderID);
	glAttachShader(m_ProgramID, m_FragmentShader->ShaderID);
	glLinkProgram(m_ProgramID);
}

void OpenGLProgram::FreeProgram()
{
	glDeleteProgram(m_ProgramID);
	m_ProgramID = 0;
}