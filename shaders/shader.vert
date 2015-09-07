#version 450 core

in vec3 pos;
in vec4 col;
in vec3 nor;

smooth out vec4 color;
smooth out vec3 normal;

uniform mat4 mvp;

void main()
{
	color = col;
	normal = mat3(mvp) * nor;
	gl_Position = mvp * vec4(pos, 1);
}