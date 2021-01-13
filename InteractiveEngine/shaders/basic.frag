#version 330 core
in vec4 vColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D uTexture;

void main()
{
	color = texture(uTexture, texCoord) * vColor;
}