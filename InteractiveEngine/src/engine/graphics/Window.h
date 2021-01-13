#pragma once
#include <string>

class Engine;
struct GLFWwindow;
class Window
{
public:
	Window(Engine* engine);
	~Window();

private:
	GLFWwindow* GlWindow;
	unsigned int Width;
	unsigned int Height;
	bool Keys[1024];

public:
	bool Initialize();
	bool CreateWindow(unsigned int& width, unsigned int& height, std::string& title);
	unsigned int GetWidth();
	unsigned int GetHeight();
	GLFWwindow* GetGlfwWindow();
	Engine* GEngine;

private:
	//TODO: Move These To A New Class Called Input Manager
	float lastX;
	float lastY;
	float xChange;
	float yChange;
	bool mouseFirstMoved;
	void CreateCallbacks();
	static void InputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);

public:
	bool* getKeys() { return Keys; }
	float GetXChange();
	float GetYChange();
};
