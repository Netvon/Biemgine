#include "stdafx.h"
#include "bmRectangle.h"

void bmRectangle::draw()
{
	/*SDL_Rect r{ x, y, width, height };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &r);*/

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void bmRectangle::init()
{
	vertexSource = R"glsl(
		#version 330 core
		layout (location = 0) in vec3 position;
		layout (location = 1) in vec3 aColor;

		out vec3 color;
		void main()
		{
			color = aColor;
			gl_Position = vec4(position, 1.0);
		}
	)glsl";

	fragmentSource = R"glsl(
		#version 330 core
		in vec3 color;
		out vec4 outColor;
		void main()
		{
			outColor = vec4(color, 1.0);
		}
	)glsl";

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
		// x      y     z     r     g     b
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 3,
		1, 2, 3
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	/*GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 0, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
