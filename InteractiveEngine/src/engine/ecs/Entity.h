#pragma once
#include <string>
#include <vector>

class Engine;
class Component;
class EntityManager;
class Entity
{
private:
	EntityManager& entityManager;
	bool isActive = false;
	std::vector<Component*> components;

public:
	std::string EntityName;
	const Engine* GEngine;

public:
	Entity(EntityManager& manager, Engine* engine);
	~Entity();

	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;

	// Template for adding components to entities.
	template <typename T, typename... TArgs>
	T* AddComponent(TArgs... args)
	{
		T* newComponent = new T(std::forward<TArgs>(args)...);

		newComponent->Owner = this;
		components.emplace_back(newComponent);
		newComponent->OnStart();

		return newComponent;
	}
};
