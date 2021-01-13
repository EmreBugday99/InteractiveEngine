#include <iostream>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Renderer.h"

#include "Texture.h"
#include "Window.h"
#include "../Engine.h"
#include "../fileio/DiskReader.h"
#include "../graphics/buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "shader/ShaderProgram.h"

// Error Callback
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cerr << "[OpenGL Debug](" << type << ") " << message << std::endl;
}

Renderer::Renderer(Window* gameWindow, Engine* engine) : GameWindow(gameWindow), GEngine(engine) {}
Renderer::~Renderer() {}

bool Renderer::Initialize()
{
	// Debug Message Callback
	glDebugMessageCallback(MessageCallback, 0);

	std::string basicVertex;
	DiskReader::ReadString(basicVertex, "shaders/basic.vert");
	std::string basicFragment;
	DiskReader::ReadString(basicFragment, "shaders/basic.frag");

	Shader = new ShaderProgram();
	Shader->AttachShader(GL_VERTEX_SHADER, basicVertex);
	Shader->AttachShader(GL_FRAGMENT_SHADER, basicFragment);
	Shader->LinkProgram();

	glm::mat4 projection(1.0f);
	const unsigned int windowWidth = GEngine->GameWindow->GetWidth();
	const unsigned int windowHeight = GEngine->GameWindow->GetHeight();

	projection = glm::perspective(45.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	Shader->UseProgram();
	std::cout << Shader->GetProgramId();
	Shader->SetUniformData("projection", false, projection);
	Shader->UnbindProgram();

	return true;
}

void Renderer::Render(VertexArray* vao)
{
	IndexBuffer* ibo = vao->GetIndexBuffer();
	Shader->UseProgram();

	vao->Bind();
	ibo->Bind();
	vao->GetTexture()->Bind();

	glDrawElements(GL_TRIANGLES, ibo->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);

	vao->GetTexture()->Unbind();
	ibo->Unbind();
	vao->Unbind();
	Shader->UnbindProgram();
}