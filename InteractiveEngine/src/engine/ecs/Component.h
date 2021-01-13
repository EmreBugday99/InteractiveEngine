#pragma once

class Entity;
class Component
{
public:
	Entity* Owner;

public:
	Component();
	virtual ~Component();
	virtual void OnStart();
	virtual void EarlyUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void BeforeRender();
	virtual void Render();
};
