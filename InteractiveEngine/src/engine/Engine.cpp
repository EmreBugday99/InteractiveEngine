#include "Engine.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Renderer.h"
#include "graphics/Window.h"
#include "ecs/EntityManager.h"

Engine::Engine()
{
	isRunning = false;
}
Engine::~Engine()
{
	Stop();
}

bool Engine::IsRunning() { return isRunning; }

bool Engine::Initialize(unsigned int& width, unsigned int& height, std::string& title)
{
	GameWindow = new Window(this);
	RenderEngine = new Renderer(GameWindow, this);
	ECSManager = new EntityManager(this);

	if (GameWindow->Initialize() == false)
	{
		std::cerr << "Error: Failed Window Initialization!" << std::endl;
		return false;
	}

	if (GameWindow->CreateWindow(width, height, title) == false)
	{
		std::cerr << "Error: Failed Window Creation!" << std::endl;
		return false;
	}

	if (RenderEngine->Initialize() == false)
	{
		std::cerr << "Error: Failed To Initialize Render Engine" << std::endl;
		return false;
	}

	return true;
}

bool Engine::Start()
{
	if (IsRunning())
		return false;

	isRunning = true;

	Update();

	return true;
}

void Engine::LoadLevel(int levelNumber)
{
}

void Engine::ProcessInput()
{
}

void Engine::Update()
{
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	while (IsRunning())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		for (Entity* entity : ECSManager->GetAllEntities())
		{
			entity->Update(deltaTime);
			entity->Render();
		}

		glfwSwapBuffers(GameWindow->GetGlfwWindow());
		glfwPollEvents();
	}

	glfwSetWindowShouldClose(GameWindow->GetGlfwWindow(), true);
	delete(ECSManager);
	delete(RenderEngine);
	delete(GameWindow);
}
void Engine::Stop()
{
	isRunning = false;
}