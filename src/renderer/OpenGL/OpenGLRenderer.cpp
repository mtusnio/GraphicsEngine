#include "OpenGLRenderer.h"

#include <cmath>

#include "OpenGLHeader.h"

#include "../Model.h"
#include "../../scene/IScene.h"
#include "../../entities/Entity.h"

#include "../../math/Vector.h"
#include "../../math/Angle.h"

#include "OpenGLTexture.h"

OpenGLRenderer::OpenGLRenderer(IGame & game)
{
	m_Game = &game;
}

void OpenGLRenderer::PrepareView() const
{
	int width, height;

	glfwGetFramebufferSize(m_Game->GetWindow(), &width, &height);
	float aspect = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);


	InitializeProjectionMatrix(90.0f, aspect, 0.5f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLRenderer::RenderScene(const IScene & scene, const Vector & cameraPosition, const Angle & cameraRotation) const
{
	PrepareView();

	RotateCurrentMatrix(-cameraRotation);
	TranslateCurrentMatrix(-cameraPosition);

	RenderObjects(cameraPosition, cameraRotation, scene);

	glfwSwapBuffers(m_Game->GetWindow());
}

void OpenGLRenderer::RenderObjects(const Vector & cameraPosition, const Angle & cameraRotation, const IScene & scene) const
{
	auto entities = scene.GetEntitySystem().GetEntities();

	for (auto pair : entities)
	{
		glPushMatrix();
		Entity * ent = pair.second;
		_ASSERT(ent != nullptr);

		Vector diff = ent->GetPosition() - cameraPosition;

		TranslateCurrentMatrix(diff);
		RotateCurrentMatrix(ent->GetRotation());
		const Model * pModel = pair.second->GetModel();

		_ASSERT(pModel != nullptr);

		for (const Model::Mesh * mesh : pModel->Meshes)
		{
			_ASSERT(mesh != nullptr);

			if (mesh->VBOs.size() > 0)
			{
				// Render using VBO
				DrawMeshVBOs(*mesh);
			}
			else
			{
				DrawMesh(*mesh);
			}
		}
		

		glPopMatrix();
		

	}
}

void OpenGLRenderer::DrawMesh(const Model::Mesh & mesh) const
{
	// Basic rendering using glBegin/glEnd for now
	for (auto matPair : mesh.Materials)
	{
		auto range = matPair.first;
		const Material * mat = matPair.second;
		if (mat)
		{
			const OpenGLTexture * diffuse = static_cast<const OpenGLTexture*>(mat->DiffuseTex.get());

			if (diffuse)
			{
				_ASSERT(diffuse->TextureID != 0);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, diffuse->TextureID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}
			else
				glDisable(GL_TEXTURE_2D);


		}
		else
		{
			glDisable(GL_TEXTURE_2D);
		}

		

		bool hasUVs = !mesh.UVs.empty();
		bool hasNormals = !mesh.Normals.empty();

		glBegin(GL_TRIANGLES);
		for (unsigned int i = range.first; i < range.second; i++)
		{
			int indice = mesh.Indices[i];

		
			if (hasUVs)
				glTexCoord2f(mesh.UVs[indice].first, mesh.UVs[indice].second);

			if (hasNormals)
			{
				Vector normal = ConvertToView(mesh.Normals[indice]);
				glNormal3f(normal.x, normal.y, normal.z);
			}
				
			Vector vec = ConvertToView(mesh.Vertices[indice]);
			//float max = fmax(vec.x, fmax(vec.z, vec.y));
			//glColor3f(vec.x / max, vec.y / max, vec.z / max);
			if (mat)
				glColor3f(mat->Diffuse[0], mat->Diffuse[1], mat->Diffuse[2]);
			glVertex3f(vec.x, vec.y, vec.z);
		}
		glEnd();
	
	}

}

void OpenGLRenderer::DrawMeshVBOs(const Model::Mesh & mesh) const
{

}

void OpenGLRenderer::InitializeProjectionMatrix(float fov, float aspect, float near, float far) const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float e = 1.f / tanf(fov / 2.0f);
	float width = near * e;
	glFrustum(-width, width, -width/aspect, width/aspect, near, far);
}

void OpenGLRenderer::TranslateCurrentMatrix(const Vector & translation) const
{
	Vector v = ConvertToView(translation);
	glTranslatef(v.x, v.y, v.z);
}

void OpenGLRenderer::RotateCurrentMatrix(const Angle & rotation) const
{
	Angle ang = ConvertToView(rotation);
	glRotatef(ang.x, 1.f, 0, 0);
	glRotatef(ang.y, 0, 1.f, 0);
	glRotatef(ang.z, 0, 0, 1.f);
}

Vector OpenGLRenderer::ConvertToView(const Vector & vec) const
{
	return Vector(-vec.y, vec.z, -vec.x);
}

Angle OpenGLRenderer::ConvertToView(const Angle & ang) const
{
	return Angle(ang.y, ang.z, -ang.x);
}