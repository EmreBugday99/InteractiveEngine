#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "engine/Engine.h"
#include "engine/components/Mesh3D.h"
#include "engine/ecs/EntityManager.h"
#include "engine/fileio/DiskReader.h"
#include "engine/graphics/Window.h"
#include "engine/graphics/shader/ShaderProgram.h"
#include "engine/components/Camera.h"
#include "engine/ecs/Entity.h"
#include "engine/graphics/Texture.h"

int main(int argc, char* argv[])
{
	std::cout << "Game simulation is being initialized..." << std::endl;
	std::vector<Mesh3D*> meshList;

	const float toRadians = 3.14159265f / 180.0f;

	std::string title = "Interactive Engine";
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;

	Engine* engine = new Engine();
	engine->Initialize(windowWidth, windowHeight, title);

	Entity* entity1 = engine->ECSManager->CreateEntity();
	Mesh3D* obj1 = entity1->AddComponent<Mesh3D>();

	//Entity* entity2 = engine->ECSManager->CreateEntity();
	//Mesh3D* obj2 = entity2->AddComponent<Mesh3D>();

	Entity* CameraEntity = engine->ECSManager->CreateEntity();
	Camera* camera = CameraEntity->AddComponent<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 1.0f);

	unsigned int indices[] =
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	float vertices[] =
	{
		// x     y     z     u     v
		-1.0f, -1.0f, 0.0f,	0.0f, 0.0f,
		 0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.5f, 1.0f
	};

	obj1->CreateMesh(vertices, indices, sizeof(vertices), sizeof(indices), "textures/brick.png");
	meshList.push_back(obj1);

	engine->Start();

	std::cout << "AAAAA" << std::endl;

	return 0;
}