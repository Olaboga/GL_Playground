#include "Mesh.h"

Mesh::Mesh(const std::string path)
{
	std::ifstream modelfile;
	modelfile.open(path.c_str(), std::ios_base::in);

	if (!modelfile.good())
	{
		std::cerr << "Mesh.cpp: Cannot load model file (" << path << ")" << std::endl;
	}

	std::string line;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;
	std::vector<Vertex> verticesVector;

	while (getline(modelfile, line))
	{
		if (line[0] == '#')
			continue;
		
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				glm::vec3 v;
				sscanf_s(line.c_str(), "%*s %f %f %f", &v.x, &v.y, &v.z);
				tempVertices.push_back(v);
			}
			else if (line[1] == 'n')
			{
				glm::vec3 n;
				sscanf_s(line.c_str(), "%*s %f %f %f", &n.x, &n.y, &n.z);
				tempNormals.push_back(n);
			}
		}
		else if (line[0] == 'f')
		{
			std::vector<std::string> elems;
			std::stringstream s(line);
			std::string item;
			while (getline(s, item, ' '))
			{
				elems.push_back(item);
			}

			if (elems.size() != 4)
			{
				std::cerr << "Mesh.cpp: error parsing file (" << path << ")!" << std::endl;
			}

			for (int i = 1; i < 4; ++i)
			{
				std::stringstream s(elems[i]);
				std::string item;
				std::vector<int> vs;
				while (getline(s, item, '/'))
				{
					vs.push_back(atoi(item.c_str()) - 1);
				}

				if (vs.size() != 3)
				{
					std::cerr << "Mesh.cpp: error parsing file (" << path << ")!" << std::endl;
				}

				Vertex vert;
				vert.pos = tempVertices[vs[0]];
				vert.col = glm::vec4(.5f, .5f, .5f, 1.f);
				vert.nrm = vs[2] != -1 ? tempNormals[vs[2]] : glm::vec3(0.f, 1.f, 0.f);

				verticesVector.push_back(vert);
			}
		}
	}

	vertCount = verticesVector.size();
	verts = (Vertex*)malloc(vertCount * sizeof(Vertex));
	for (int i = 0; i < vertCount; ++i)
	{
		verts[i] = verticesVector[i];
	}

	std::cout << "Mesh.cpp: model loaded (" << path << ")." << std::endl;
}

Mesh::~Mesh()
{
	delete(verts);
}