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
	if (ID != 0)
		glDeleteVertexArrays(1, &ID);

	if (Indice != 0)
		glDeleteBuffers(1, &Indice);
}
void OpenGLVAO::Register(Model & model, unsigned int meshIndex, unsigned int materialIndex)
{
	_ASSERT(meshIndex < model.Meshes.size());
	const Model::Mesh & mesh = *model.Meshes[meshIndex];
	_ASSERT(mesh.Vertices.size() > 0);

	// Generate our VAO here
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);

	if (mesh.VAOs.size() > 0)
	{
		const OpenGLVAO * vao = static_cast<const OpenGLVAO*>(mesh.VAOs[0]);


		// Use the same vertices, only indices change
		Vertices = vao->Vertices;
		Normals = vao->Normals;
		Texcoords = vao->Texcoords;
	}
	else
	{
		glGenBuffers(1, &Vertices);
		glBindBuffer(GL_ARRAY_BUFFER, Vertices);
		glBufferData(GL_ARRAY_BUFFER, mesh.Vertices.size() * 3 * sizeof(GLfloat), &mesh.Vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		/*if (mesh.Normals.size() > 0)
		{
			glGenBuffers(1, &Normals);
			glBindBuffer(GL_ARRAY_BUFFER, Normals);
			glBufferData(GL_ARRAY_BUFFER, mesh.Normals.size() * 3 * sizeof(GLfloat), &mesh.Vertices[0], GL_STATIC_DRAW);
		}*/
		
		if (mesh.UVs.size() > 0)
		{
			glGenBuffers(1, &Texcoords);
			glBindBuffer(GL_ARRAY_BUFFER, Texcoords);
			glBufferData(GL_ARRAY_BUFFER, mesh.UVs.size() * 2 * sizeof(GLfloat), &mesh.UVs[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		
	}

	_ASSERT(materialIndex < mesh.Materials.size());
	
	Model::Mesh::Range range = mesh.Materials[materialIndex].first;

	// Not very fast at the moment, we literally copy the indices and then
	// pass the memory index. Possibly just get the proper spot & range
	// and use pointer arithmetics to speed it up?
	std::vector<unsigned int> indices(range.second - range.first);
	for (unsigned int i = range.first; i < range.second; i++)
	{
		indices.push_back(mesh.Indices[i]);
	}
	Size = indices.size();
	
	glGenBuffers(1, &Indice);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Indice);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}


void OpenGLVAO::DestroySharedData()
{
	if (Vertices != 0)
		glDeleteBuffers(1, &Vertices);
	if (Normals != 0)
		glDeleteBuffers(1, &Normals);
	if (Texcoords != 0)
		glDeleteBuffers(1, &Texcoords);
}