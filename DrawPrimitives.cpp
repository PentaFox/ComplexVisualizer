#include "DrawPrimitives.h"

# define M_PI           3.14159265358979323846

DrawPrimitives::DrawPrimitives()
{
}


DrawPrimitives::~DrawPrimitives()
{
}

vector<Vertex> DrawPrimitives::DrawPlane(float width, float length, glm::vec3 color)
{
	float a, b, c, d;
	a = width * -0.5;
	b = width * 0.5;
	c = length * -0.5;
	d = length * 0.5;

	vector<Vertex> plane;
	plane.push_back(Vertex{ a, c, 0.0, color[0], color[1], color[2] });
	plane.push_back(Vertex{ a , d , 0.0, color[0],color[1],color[2] });
	plane.push_back(Vertex{ b , d , 0.0, color[0],color[1],color[2] });
	plane.push_back(Vertex{ a , c , 0.0, color[0],color[1],color[2] });
	plane.push_back(Vertex{ b , c , 0.0, color[0],color[1],color[2] });
	plane.push_back(Vertex{ b , d , 0.0, color[0],color[1],color[2] });
	
	return plane ;
}

vector<Vertex> DrawPrimitives::DrawCircle(float radius, int iterations, glm::vec3 color)
{
	vector<Vertex>cirle;
	vector<Vertex>cirlePoints;
	for (int i = 0; i < iterations; i++) {
		float x = radius * cosf(i * 2 * M_PI / iterations);
		float y = radius * sinf(i * 2 * M_PI / iterations);
		cirlePoints.push_back(Vertex{ x,y,0.0, color[0], color[1], color[2] });
	}
	for (int i = 0; i < iterations; i++)
	{
		Vertex mid = { 0.0, 0.0, 0.0, color[0], color[1], color[2] };
		cirle.push_back(cirlePoints[i]);
		cirle.push_back(mid);
		cirle.push_back(cirlePoints[(i+1)%cirlePoints.size()]);
	}
	return cirle;
};
