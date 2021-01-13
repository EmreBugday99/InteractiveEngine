#pragma once
#include <vector>
#include "Entity.h"
#include "../Engine.h"

class Engine;
class EntityManager
{
private:
	std::vector<Entity*> entities;
	Engine* GEngine;

public:
	EntityManager(Engine* engine);
	~EntityManager();

	void Update(float deltaTime);
	void Render();
	void DestroyAllEntities();

	Entity* CreateEntity();
	bool HasAnyEntity() const;
	std::vector<Entity*> GetAllEntities() const;
	unsigned int GetTotalEntityCount() const;
};
