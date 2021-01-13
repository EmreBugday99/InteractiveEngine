#include "IndexBuffer.h"

#include <iostream>
#include <GL/glew.h>

IndexBuffer::IndexBuffer(VertexArray* ownerVao, unsigned int bufferId)
	: BufferId(bufferId), OwnerVAO(ownerVao), IndicesCount(0)
{
	//std::cout << "Created IBO: " << BufferId << std::endl;
}

IndexBuffer::~IndexBuffer()
{
	//std::cout << "Deleted IBO: " << BufferId << std::endl;
	glDeleteBuffers(1, &BufferId);
}
void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId); }
void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
const unsigned IndexBuffer::GetBufferId() const { return BufferId; }
void IndexBuffer::SetBufferId(unsigned int id) { BufferId = id; }
const unsigned IndexBuffer::GetIndicesCount() const { return IndicesCount; }

void IndexBuffer::SetData(unsigned int* data, unsigned int dataSize)
{
	Bind();

	IndicesCount = dataSize;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	Unbind();
}