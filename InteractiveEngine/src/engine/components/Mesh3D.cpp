#include "Mesh3D.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../Engine.h"
#include "../graphics/Renderer.h"
#include "../graphics/buffers/VertexArray.h"
#include "../graphics/buffers/IndexBuffer.h"
#include "../graphics/buffers/VertexBuffer.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../graphics/shader/ShaderProgram.h"

Mesh3D::Mesh3D() : VAO(nullptr) {}
Mesh3D::~Mesh3D()
{
	//TODO: Remove from Entity Manager!!!
	//
	// Deleting VAO will create a chain deallocation reaction.
	// VAO's deconstructor will delete all of it's child member classes (VBOs & IBO).
	delete(VAO);
}

void Mesh3D::OnStart() {}
void Mesh3D::EarlyUpdate(float deltaTime) {}
void Mesh3D::Update(float deltaTime) {}
void Mesh3D::LateUpdate(float deltaTime) {}

void Mesh3D::Render()
{
	if (VAO == nullptr)
	{
		std::cout << "Null PTR" << std::endl;
	}
	glm::mat4 model(1.0f);
	glm::vec3 offset(0.0f, 0.0f, -2.5f);
	//model = glm::translate(model, offset);
	//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

	Owner->GEngine->RenderEngine->Shader->UseProgram();
	Owner->GEngine->RenderEngine->Shader->SetUniformData("model", false, model);
	Owner->GEngine->RenderEngine->Render(VAO);
	Owner->GEngine->RenderEngine->Shader->UnbindProgram();
}
void Mesh3D::CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices, std::string textureLocation)
{
	VAO = new VertexArray();
	VAO->Bind();

	IndexBuffer* ibo = VAO->CreateIndexBuffer(indices, numOfIndices);
	ibo->Bind();
	VertexBuffer* vbo = VAO->CreateVertexBuffer(vertices, numOfVertices);
	Texture* texture = VAO->CreateTexture(textureLocation);

	vbo->Unbind();
	ibo->Unbind();
	VAO->Unbind();
}

VertexArray* Mesh3D::GetVAO() const { return VAO; }