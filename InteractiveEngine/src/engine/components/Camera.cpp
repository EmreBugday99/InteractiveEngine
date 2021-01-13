#include "Camera.h"
#include <GLFW/glfw3.h>
#include "../Engine.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../graphics/Renderer.h"
#include "../graphics/Window.h"
#include "../graphics/shader/ShaderProgram.h"

Camera::Camera(glm::vec3 startingPos, glm::vec3 startingUp, float startingYaw, float startingPitch, float startingMoveSpeed, float startingTurnSpeed)
{
	Position = startingPos;
	WorldUp = startingUp;
	Yaw = startingYaw;
	Pitch = startingPitch;
	MovementSpeed = startingMoveSpeed;
	TurnSpeed = startingTurnSpeed;

	Front = glm::vec3(0.0f, 0.0f, -1.0f);

	UpdateCamera();
}

Camera::~Camera()
{
}

void Camera::OnStart()
{
}

void Camera::EarlyUpdate(float deltaTime) {}

void Camera::Update(float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	bool* keys = Owner->GEngine->GameWindow->getKeys();

	if (keys[GLFW_KEY_W])
	{
		Position += Front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		Position -= Front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		Position -= Right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		Position += Right * velocity;
	}
}

void Camera::LateUpdate(float deltaTime)
{
	float xChange = Owner->GEngine->GameWindow->GetXChange();
	float yChange = Owner->GEngine->GameWindow->GetYChange();

	xChange *= TurnSpeed;
	yChange *= TurnSpeed ;

	Yaw += xChange;
	Pitch += yChange;

	if (Pitch > 89.0f)
		Pitch = 89.0f;

	if (Pitch < -89.0f)
		Pitch = -89.0f;

	UpdateCamera();
}

void Camera::BeforeRender()
{
	glm::mat4 view(1.0f);
	view = glm::lookAt(Position, Position + Front, Up);
	
	ShaderProgram* program = Owner->GEngine->RenderEngine->Shader;
	program->UseProgram();
	program->SetUniformData("view", false, view);
	program->UnbindProgram();
}

void Camera::Render() {}

void Camera::UpdateCamera()
{
	Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front.y = sin(glm::radians(Pitch));
	Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(Front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}