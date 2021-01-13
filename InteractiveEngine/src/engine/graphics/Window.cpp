#include "Window.h"

#include <iostream>
#include "gl/glew.h"
#include <GLFW/glfw3.h>

#include "../Engine.h"

Window::Window(Engine* engine) : GEngine(engine)
{
	xChange = 0.0f;
	yChange = 0.0f;
}
Window::~Window() {}

bool Window::Initialize()
{
	if (GlWindow != nullptr) return false;

	if (glfwInit() == false)
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	for (bool key : Keys)
	{
		key = false;
	}

	return true;
}

bool Window::CreateWindow(unsigned int& width, unsigned int& height, std::string& title)
{
	if (GlWindow != nullptr) return false;

	GlWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (GlWindow == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(GlWindow);

	CreateCallbacks();
	glfwSetInputMode(GlWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error: Failed to initialize GLEW" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glfwSetWindowUserPointer(GlWindow, this);

	Width = width;
	Height = height;
	return true;
}

unsigned int Window::GetWidth()
{
	return Width;
}

unsigned int Window::GetHeight()
{
	return Height;
}

struct GLFWwindow* Window::GetGlfwWindow()
{
	return GlWindow;
}

void Window::CreateCallbacks()
{
	glfwSetKeyCallback(GlWindow, InputCallback);
	glfwSetCursorPosCallback(GlWindow, MouseCallback);
}

void Window::InputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	Window* localWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		delete(localWindow->GEngine);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			localWindow->Keys[key] = true;
			printf("Pressed %d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			localWindow->Keys[key] = false;
			printf("Release %d\n", key);
		}
	}
}

void Window::MouseCallback(struct GLFWwindow* window, double xPos, double yPos)
{
	Window* localWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (localWindow->mouseFirstMoved)
	{
		localWindow->lastX = xPos;
		localWindow->lastY = yPos;
		localWindow->mouseFirstMoved = false;
	}

	localWindow->xChange = xPos - localWindow->lastX;
	localWindow->yChange = localWindow->lastY - yPos;

	localWindow->lastX = xPos;
	localWindow->lastY = yPos;

	printf("x: %.6f, y:%.6f \n", localWindow->xChange, localWindow->yChange);
}

float Window::GetXChange()
{
	float change = xChange;
	xChange = 0.0f;
	return change;
}

float Window::GetYChange()
{
	float change = yChange;
	yChange = 0.0f;
	return change;
}
