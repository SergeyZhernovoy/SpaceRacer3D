#include "LoadObj.h"

const bool LoadObj(
	const char * filepath,
	std::vector<Vec3>& o_vertices,
	std::vector<Vec3>& o_normals,
	Primitive& o_primitive
	)
{
	std::vector<unsigned int> vertices, normals;
	std::vector<Vec3> temp_vertices;
	std::vector<Vec3> temp_normals;
	FILE * file = fopen(filepath, "r");
	if (file == NULL)
	{
		return false;
	}
	bool finished = false;
	while (!finished)
	{
		char line[128];
		int check = fscanf(file, "%s", line);
		if (check == EOF)
		{
			finished = true;
		}
		else
		{
			if (strcmp(line, "v") == 0)
			{
				Vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(line, "vn") == 0)
			{
				Vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(line, "f") == 0)
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[4], normalIndex[4];
				int matches = fscanf(file, "%d//%d %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2], &vertexIndex[3], &normalIndex[3]);
				switch (matches)
				{
				case 6:
					o_primitive = Primitive::Triangles;
					vertices.push_back(vertexIndex[0]);
					vertices.push_back(vertexIndex[1]);
					vertices.push_back(vertexIndex[2]);
					normals.push_back(normalIndex[0]);
					normals.push_back(normalIndex[1]);
					normals.push_back(normalIndex[2]);
					break;
				case 8:
					o_primitive = Primitive::Quads;
					vertices.push_back(vertexIndex[0]);
					vertices.push_back(vertexIndex[1]);
					vertices.push_back(vertexIndex[2]);
					vertices.push_back(vertexIndex[3]);
					normals.push_back(normalIndex[0]);
					normals.push_back(normalIndex[1]);
					normals.push_back(normalIndex[2]);
					normals.push_back(normalIndex[3]);
					break;
				default:
					char dummy[1000];
					fgets(dummy, 1000, file);
					break;
				}
			}
		}
	}
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		unsigned int vertexIndex = vertices[i];
		unsigned int normalIndex = normals[i];
		Vec3 vertex = temp_vertices[vertexIndex - 1];
		Vec3 normal = temp_normals[normalIndex - 1];
		o_vertices.push_back(vertex);
		o_normals.push_back(normal);
	}
	return true;
}
