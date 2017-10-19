#define GLFW_INCLUDE_GLU
#include "glew.h"
#include "glfw3.h"

#include "PNGReader.h"
#include "LodePNG.h"
#include <vector>
#include <iostream>

PNGReader::PNGReader()
{
}


PNGReader::~PNGReader()
{
}

unsigned char* PNGReader::readPNG(char* filename)
{
	std::vector<unsigned char> data ;

	unsigned width, height;

	unsigned error = lodepng::decode(data, width, height, filename);
	std::cout << "lodePNG : Decode PNG at " << filename << "\n" << "errorcode" << unsigned(error);
	std::cout << "Image has" << unsigned(width) << "x" << unsigned(height) << "pixel";

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_1D, tex);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_1D);

	glTexImage1D(GL_TEXTURE_1D, 0, 4, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*) data.data());
	glEnable(GL_TEXTURE_1D);
	
	return data.data();

}