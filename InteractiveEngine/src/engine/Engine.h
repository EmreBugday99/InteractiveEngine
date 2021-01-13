#pragma once
#include <string>

class Renderer;
class Window;
class EntityManager;

class Engine {
private:
	bool isRunning;

public:
	Renderer* RenderEngine;
	Window* GameWindow;
	EntityManager* ECSManager;

public:
	Engine();
	~Engine();
	bool IsRunning();
	bool Initialize(unsigned int& width, unsigned int& height, std::string& title);
	bool Start();
	void LoadLevel(int levelNumber);
	void ProcessInput();
	void Update();
	void Stop();
};
