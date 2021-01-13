#pragma once
#include "../ecs/Component.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera : public Component
{
private:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float TurnSpeed;

public:
	Camera(glm::vec3 startingPos, glm::vec3 startingUp, float startingYaw, float startingPitch, float startingMoveSpeed, float startingTurnSpeed);
	~Camera() override;
	void OnStart() override;
	void EarlyUpdate(float deltaTime) override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void BeforeRender() override;
	void Render() override;
	
	void UpdateCamera();
};
