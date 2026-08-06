#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform float texturePercent;

float hash(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return float(x) / 4294967295.0;
}

void main()
{
	float color;

	color = hash(gl_PrimitiveID);

	vec3 pixel = vec3(color, color, color);

	FragColor = vec4(pixel, 1.0f);
	FragColor = (FragColor * (1 - texturePercent)) + (texture(ourTexture, TexCoord) * texturePercent);
}
