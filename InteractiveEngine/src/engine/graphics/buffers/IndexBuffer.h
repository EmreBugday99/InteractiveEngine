#pragma once

class VertexArray;
class IndexBuffer
{
private:
	unsigned int BufferId;
	VertexArray* OwnerVAO;
	unsigned int IndicesCount;

public:
	IndexBuffer(VertexArray* ownerVao, unsigned int bufferId);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	const unsigned int GetBufferId() const;
	void SetBufferId(unsigned int id);
	const unsigned int GetIndicesCount() const;

	void SetData(unsigned int* data, unsigned int dataSize);
};
