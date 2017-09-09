#pragma once
#include "glew.h"
#include "glfw3.h"

#include<iostream>
#include <fstream>
#include <vector>
#include<string>
#include <stdlib.h>
using namespace std;

// This code has been taken from 
// : http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/

class Shaderloader
{
	public:
		Shaderloader();
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};

