#pragma once

class VertexArray;

class VertexBuffer
{
private:
	unsigned int BufferId;
	unsigned int VerticesCount;
	VertexArray* OwnerVAO;

public:
	VertexBuffer(VertexArray* ownerVao, unsigned int bufferId);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	void SetBufferId(unsigned int id);
	const unsigned int GetBufferId() const;
	const unsigned int GetVerticesCount() const;

	void SetData(float* data, unsigned int dataSize);
};
