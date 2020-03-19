#pragma once

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

enum Primitive
{
	Triangles = 0,
	Quads = 1
};

struct Vec2
{
	Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vec2(const float p_x, const float p_y)
	{
		x = p_x;
		y = p_y;
	}

	float x;
	float y;
};

struct Vec3
{
	Vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vec3(const float p_x, const float p_y, const float p_z)
	{
		x = p_x;
		y = p_y;
		z = p_z;
	}

	float x;
	float y;
	float z;
};

const bool LoadObj(
	const char * filepath, 
	std::vector<Vec3> &o_vertices, 
	std::vector<Vec3> &o_normals,
	Primitive &o_primitive
);