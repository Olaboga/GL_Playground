#version 450 core

smooth in vec4 color;
smooth in vec3 normal;

out vec4 out_col;

void main()
{
	out_col = color * dot(normalize(vec3( 0, 0.1, -1)), normal);
}