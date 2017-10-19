#pragma once
#define GLFW_INCLUDE_GLU
#include "glew.h"
#include "glfw3.h"


#define GLM_ENABLE_EXPERIMENTAL
#include "..\glm-0.9.9-a1\glm\glm.hpp"
#include"..\glm-0.9.9-a1\glm\gtx\transform.hpp"

#include<vector>
using namespace std;

static const struct Vertex
{
	float x, y, z;
	float r, g, b;
} vertices;

class DrawPrimitives
{
public:
	DrawPrimitives();
	~DrawPrimitives();

	vector<Vertex> DrawPlane(float height, float length, glm::vec3 color);
	vector<Vertex> DrawCircle(float radius, int iterations, glm::vec3 color);

};

