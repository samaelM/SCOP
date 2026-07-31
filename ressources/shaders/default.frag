#version 330 core

//in vec2 TexCoord;

out vec4 FragColor;

//uniform sampler2D ourTexture;

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
//	vec3 pixel = vec3(0, 0.7, 0);

	FragColor = vec4(pixel, 1.0f); // * dt pour fade ou un truc du genre
//	FragColor = texture(ourTexture, TexCoord) ;
}
