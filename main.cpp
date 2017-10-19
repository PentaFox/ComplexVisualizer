#define GLFW_INCLUDE_GLU
#include "glew.h"
#include "glfw3.h"

#define MANDELBROT

#define GLM_ENABLE_EXPERIMENTAL
#include "..\glm-0.9.9-a1\glm\glm.hpp"
#include"..\glm-0.9.9-a1\glm\gtx\transform.hpp"
 

#include <iostream>
#include <vector>
using namespace std;

#include "Shaderloader.h"
#include "DrawPrimitives.h"
#include "PNGReader.h"

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600
#define WINDOWTITLE "FOXX"


GLubyte indices[] =
{
	0 , 1 , 2 , 3, 6, 7, 4, 5 

};

float points[] = {
	-0.5f,  -0.5f,  0.0f, 1.0, 0.0, 0.0,
	0.5f, -0.5f,  0.0f, 0.0, 1.0, 0.0,
	0.0f, 0.5f,  0.0f, 0.0, 0.0, 1.0
};

void errorCallback(int error, const char* callback);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char* agrv[])
{
	if (!glfwInit())
		glfwTerminate();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window;
	window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, WINDOWTITLE, NULL, NULL);

	
	//SET CALLBACKS
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);
	
	
	//SET CONTEXT
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to init GLEW\n");
		return -1;
	}

	glfwShowWindow(window);

	//setUpPrimitives
	DrawPrimitives drawer;
	vector<Vertex> vertices = drawer.DrawPlane(1, 1, glm::vec3(1.0f, 0.8f, 1.0f));
	//vector<Vertex> vertices = drawer.DrawCircle(1, 100, glm::vec3(0.0f, 1.0f, 0.0f));

	
	//SET Vertex Buffer
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//Vertex Array object
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

	//SET Index Buffer
	/* GLuint elementbuffer = 0;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	*/
	//SET SHADER   //vertex shader not in place
	Shaderloader shaderloader;
	GLuint program = shaderloader.LoadShaders("vertexFile.glsl", "mandelbrot.glsl");
	glUseProgram(program);


	//Load GLSL Uniforms
	GLuint centerLoc = glGetUniformLocation(program, "center");
	glUniform2f(centerLoc, 0.0, 0.7);
	
	


	PNGReader pngReader;

	unsigned char * texture = pngReader.readPNG("pal.png");

	//Enable Depthbuffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwShowWindow(window);



	while (!glfwWindowShouldClose(window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Perspective Camera
		glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		float ratio = (float) WINDOWWIDTH / (float) WINDOWHEIGHT;
		glm::mat4 Proj = glm::perspective(glm::radians(30.0f), ratio, 0.01f, 300.0f);

		float elapsedTime = glfwGetTime();

		glm::mat4 Model = glm::mat4(1.0f); //identity
		//Model = Model * glm::rotate(elapsedTime, glm::vec3(0, 1, 0));

		glm::mat4 MVP =  Model;
		//MVP = Proj * View * Model;
		GLint mvpLoc = glGetUniformLocation(program, "MVP");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE,&MVP[0][0]);

		glUseProgram(program);
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		//glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, (GLvoid*)0);
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size()); 


		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);
		glTexCoord2f(1, 0);
		glVertex2f(1, -1);
		glTexCoord2f(1, 1);
		glVertex2f(1, 1);
		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
		glEnd();

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);

	}
}


void errorCallback(int error, const char* dest)
{
	fprintf(stderr, "Error: %s\n", dest);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

