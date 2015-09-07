#include "glm\glm.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Vertex
{
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec3 nrm;

	Vertex()
	{
		pos = glm::vec3(0.f);
		col = glm::uvec4(1.f);
	}

	Vertex(glm::vec3 position)
	{
		pos = position;
		col = glm::uvec4(1.f);
	}

	Vertex(int x, int y, int z)
	{
		pos = glm::vec3((float)x, (float)y, (float)z);
		col = glm::vec4(1.f, 0.f, 1.f, 1.f);
	}

	Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal)
	{
		pos = position;
		col = glm::vec4(color.x, color.y, color.z, 1.f);
		nrm = normal;
	}
};

class Mesh
{
public:
	int vertCount;
	Vertex* verts;

	Mesh(const std::string path);
	~Mesh();
};
