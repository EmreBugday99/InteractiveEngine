#pragma once
#include <string>
#include <vector>

class Texture;
class IndexBuffer;
class VertexBuffer;
class VertexArray
{
private:
	unsigned int ArrayId;
	std::vector<VertexBuffer*> VBuffers;
	IndexBuffer* IBuffer;
	Texture* AttachedTexture;

public:
	VertexArray();
	~VertexArray();

	VertexBuffer* CreateVertexBuffer(float* data, unsigned int dataSize);
	IndexBuffer* CreateIndexBuffer(unsigned int* data, unsigned int dataSize);
	Texture* CreateTexture(std::string fileLocation);

	IndexBuffer* GetIndexBuffer() const;
	std::vector<VertexBuffer*>* GetVertexBuffers();
	Texture* GetTexture();

	void Bind() const;
	void BindTexture() const;
	void Unbind() const;
};
