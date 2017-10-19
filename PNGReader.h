#pragma once

class PNGReader
{
public:
	PNGReader();
	~PNGReader();

	unsigned char* readPNG(char* filename);
};

