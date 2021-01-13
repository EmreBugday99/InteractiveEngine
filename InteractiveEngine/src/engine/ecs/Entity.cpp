#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"

Entity::Entity(EntityManager& manager, Engine* engine)
: entityManager(manager), GEngine(engine)
{
	this->isActive = true;
	EntityName = "Entity " + std::to_string(manager.GetTotalEntityCount());
}

Entity::~Entity()
{
	for (Component* component: components)
	{
		delete(component);
	}
}

void Entity::Update(float deltaTime)
{
	for (Component*& component : components)
	{
		component->EarlyUpdate(deltaTime);
		component->Update(deltaTime);
		component->LateUpdate(deltaTime);
	}
}

void Entity::Render()
{
	for (Component*& component : components)
	{
		component->BeforeRender();
		component->Render();
	}
}

void Entity::Destroy()
{
	this->isActive = false;
}

bool Entity::IsActive() const
{
	return isActive;
}