#include "VertexBuffer.h"

#include <iostream>

#include "VertexArray.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(VertexArray* ownerVao, unsigned int bufferId)
	: BufferId(bufferId), VerticesCount(0), OwnerVAO(ownerVao)
{
	//std::cout << "Created VBO: " << BufferId << std::endl;
}

VertexBuffer::~VertexBuffer()
{
	//std::cout << "Deleted VBO: " << BufferId << std::endl;
	glDeleteBuffers(1, &BufferId);
}
void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, BufferId); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
void VertexBuffer::SetBufferId(unsigned int id) { BufferId = id; }
const unsigned int VertexBuffer::GetBufferId() const { return BufferId; }
const unsigned int VertexBuffer::GetVerticesCount() const { return VerticesCount; }

void VertexBuffer::SetData(float* data, unsigned int dataSize)
{
	Bind();

	VerticesCount = dataSize;
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 5, 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 5, (void*)(sizeof(data[0]) * 3));
	glEnableVertexAttribArray(1);
	Unbind();
}