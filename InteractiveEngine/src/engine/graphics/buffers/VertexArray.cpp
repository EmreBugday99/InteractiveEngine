#include "VertexArray.h"
#include <iostream>
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "../Texture.h"

VertexArray::VertexArray()
	: ArrayId(0), IBuffer(nullptr), AttachedTexture(nullptr)
{
	glGenVertexArrays(1, &ArrayId);
	//std::cout << "Created VAO: " << ArrayId << std::endl;
}

VertexArray::~VertexArray()
{
	//std::cout << "Deleted VAO: " << ArrayId << std::endl;

	for (VertexBuffer* vbo : VBuffers)
	{
		if (vbo == nullptr) continue;
		delete(vbo);
	}
	VBuffers.clear();

	delete(IBuffer);
	delete(AttachedTexture);
	glDeleteVertexArrays(1, &ArrayId);
}

VertexBuffer* VertexArray::CreateVertexBuffer(float* data, unsigned int dataSize)
{
	Bind();

	unsigned int bufferId;
	glGenBuffers(1, &bufferId);

	VertexBuffer* Vbuffer = new VertexBuffer(this, bufferId);
	VBuffers.emplace_back(Vbuffer);

	Vbuffer->SetBufferId(bufferId);
	Vbuffer->SetData(data, dataSize);

	Unbind();
	return Vbuffer;
}

IndexBuffer* VertexArray::CreateIndexBuffer(unsigned int* data, unsigned int dataSize)
{
	/*
	 * If we already have an existing Index Buffer inside this Vertex Array
	 * Creating a new Index Buffer will result in memory leak
	 * as it will override the memory pointer of the current Index Buffer.
	 * A Vertex Array must have only one Index Buffer to prevent memory leak.
	 * Creating a dynamic array(vector, deque etc.) is pointless
	 * and also memory heavy for this task. Just keep only one Index Buffer and viola!
	 */
	if (IBuffer != nullptr) return nullptr;

	Bind();
	unsigned int bufferId;
	glGenBuffers(1, &bufferId);

	IBuffer = new IndexBuffer(this, bufferId);

	IBuffer->SetBufferId(bufferId);
	IBuffer->SetData(data, dataSize);

	Unbind();
	return IBuffer;
}

Texture* VertexArray::CreateTexture(std::string fileLocation)
{
	AttachedTexture = new Texture();
	AttachedTexture->LoadTexture(fileLocation);
	
	return AttachedTexture;
}

IndexBuffer* VertexArray::GetIndexBuffer() const { return IBuffer; }
std::vector<VertexBuffer*>* VertexArray::GetVertexBuffers() { return &VBuffers; }

Texture* VertexArray::GetTexture()
{
	return AttachedTexture;
}

void VertexArray::Bind() const { glBindVertexArray(ArrayId); }
void VertexArray::Unbind() const { glBindVertexArray(0); }

