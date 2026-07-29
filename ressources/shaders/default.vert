#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 2) in vec2 aTexCoord;

//out vec2 TexCoord;

//uniform float dx;
//uniform float dy;
//uniform float dz;
//
//uniform mat4 m_model;
//uniform mat4 m_projection;
//uniform mat4 m_view;


void main() {
	gl_Position = vec4(aPos, 1.0);
//	gl_Position = m_model * gl_Position;
//	gl_Position.x += dx;
//	gl_Position.y += dy;
//	gl_Position.z += dz;
//	gl_Position = m_projection * m_view * gl_Position;
//
//	TexCoord = vec2((aPos.x + 1) / 2, -(aPos.y + 1) /2);
//    float distanceCam = 1.0;
//    float perspectiveFactor = distanceCam / (distanceCam - gl_Position.z);
//	gl_Position.x *= perspectiveFactor;
//	gl_Position.y *= perspectiveFactor;
}
