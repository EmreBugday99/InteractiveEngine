#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"
#include "GL/glew.h"

Texture::Texture()
	:TextureId(0), Width(0),
	Height(0), BitDepth(0)
{
}

Texture::~Texture()
{
	ClearTexture();
}

unsigned int Texture::LoadTexture(std::string& fileLocation)
{
	FileLocation = fileLocation;
	unsigned char* textData = stbi_load(fileLocation.c_str(), &Width, &Height, &BitDepth, STBI_rgb_alpha);
	if (!textData)
	{
		printf("Failed to find %s\n", FileLocation.c_str());
		return 0;
	}

	glGenTextures(1, &TextureId);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData);
	glGenerateMipmap(GL_TEXTURE_2D);

	Unbind();

	stbi_image_free(textData);

	return TextureId;
}

unsigned Texture::GetTextureId() { return TextureId; }

void Texture::ClearTexture()
{
	glDeleteTextures(1, &TextureId);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureId);
}

void Texture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }