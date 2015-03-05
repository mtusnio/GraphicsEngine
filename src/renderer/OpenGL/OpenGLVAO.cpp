#include "OpenGLVAO.h"

#include "OpenGLHeader.h"

#include"../Model.h"

OpenGLVAO::OpenGLVAO()
{
	Vertices = 0;
	Normals = 0;
	Texcoords = 0;
	Indice = 0;
	ID = 0;
}

OpenGLVAO::~OpenGLVAO()
{

}
void OpenGLVAO::Register(const Model & model, unsigned int meshIndex, unsigned int materialIndex)
{
	_ASSERT(meshIndex < model.Meshes.size());
	const Model::Mesh & mesh = *model.Meshes[meshIndex];
	_ASSERT(mesh.Vertices.size() > 0);

	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);

	if (mesh.VAOs.size() > 0)
	{
		const OpenGLVAO * vbo = static_cast<const OpenGLVAO*>(mesh.VAOs[0]);


		// Use the same vertices, only indices change
		Vertices = vbo->Vertices;
		Normals = vbo->Normals;
		Texcoords = vbo->Texcoords;
	}
	else
	{
		glGenBuffers(1, &Vertices);
		glBindBuffer(GL_ARRAY_BUFFER, Vertices);
		glBufferData(GL_ARRAY_BUFFER, mesh.Vertices.size() * 3 * sizeof(GLfloat), &mesh.Vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		if (mesh.Normals.size() > 0)
		{
			glGenBuffers(1, &Normals);
			glBindBuffer(GL_ARRAY_BUFFER, Normals);
			glBufferData(GL_ARRAY_BUFFER, mesh.Normals.size() * 3 * sizeof(GLfloat), &mesh.Vertices[0], GL_STATIC_DRAW);
		}
		
		if (mesh.UVs.size() > 0)
		{
			glGenBuffers(1, &Texcoords);
			glBindBuffer(GL_ARRAY_BUFFER, Texcoords);
			glBufferData(GL_ARRAY_BUFFER, mesh.UVs.size() * 2 * sizeof(GLfloat), &mesh.UVs[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
		}

		
	}

	
	std::vector<int> indice;
	


	
	glBindVertexArray(0);
}
