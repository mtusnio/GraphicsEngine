#ifndef H_OPENGLPROGRAM
#define H_OPENGLPROGRAM

#include "OpenGLHeader.h"

#include "OpenGLShader.h"

#include <string>
#include <memory>

class OpenGLProgram
{
public:
	OpenGLProgram();
	~OpenGLProgram();
	
	
	GLuint GetProgramID() const { return m_ProgramID; }
	void Load(const std::shared_ptr<const OpenGLShader> & vertexShader, const std::shared_ptr<const OpenGLShader> & pixelShader);

private:
	void FreeProgram();

	GLuint m_ProgramID;

	std::shared_ptr<const OpenGLShader> m_VertexShader;
	std::shared_ptr<const OpenGLShader> m_FragmentShader;
};


#endif