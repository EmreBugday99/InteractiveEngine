#pragma once
#include <string>

#include "../ecs/Component.h"

class ShaderProgram;
class IndexBuffer;
class VertexBuffer;
class VertexArray;
class Mesh3D : public Component
{
private:
	VertexArray* VAO;

public:
	Mesh3D();
	~Mesh3D() override;

	void OnStart() override;
	void EarlyUpdate(float deltaTime) override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Render() override;

	void CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices, std::string textureLocation);
	VertexArray* GetVAO() const;

};
