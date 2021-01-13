#include "EntityManager.h"

EntityManager::EntityManager(Engine* engine) : GEngine(engine) {}

EntityManager::~EntityManager()
{
	for (Entity* entity : entities)
	{
		delete(entity);
	}
}

void EntityManager::Update(float deltaTime)
{
	for (Entity*& entity : entities)
	{
		entity->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	for (Entity*& entity : entities)
	{
		entity->Render();
	}
}

void EntityManager::DestroyAllEntities()
{
	for (Entity*& entity : entities)
	{
		entity->Destroy();
	}
}

bool EntityManager::HasAnyEntity() const
{
	return !entities.empty();
}

Entity* EntityManager::CreateEntity()
{
	auto* entity = new Entity(*this, GEngine);
	entities.emplace_back(entity);
	return entity;
}

std::vector<Entity*> EntityManager::GetAllEntities() const
{
	return entities;
}

unsigned EntityManager::GetTotalEntityCount() const
{
	return entities.size();
}
