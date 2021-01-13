#pragma once
#include <string>
class Texture
{
private:
	unsigned int TextureId;
	int Width;
	int Height;
	int BitDepth;
	std::string FileLocation;

public:
	Texture();
	~Texture();

	unsigned int LoadTexture(std::string& fileLocation);
	unsigned int GetTextureId();
	void Bind();
	void Unbind();

private:
	void ClearTexture();
};
