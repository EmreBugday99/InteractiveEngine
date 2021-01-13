#pragma once
#include <map>

class Engine;
class ShaderProgram;
class VertexArray;
class Mesh3D;
class Sprite2D;
class Window;
class Renderer
{
public:
	Window* GameWindow;
	ShaderProgram* Shader;
	Engine* GEngine;

public:
	Renderer(Window* gameWindow, Engine* engine);
	~Renderer();

	bool Initialize();
	void Render(VertexArray* vao);
};
