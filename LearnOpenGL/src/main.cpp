#include <iostream>
#include "LoadShader.h"
#include <GLFW/glfw3.h>

const GLuint NumVertices = 3;
static GLuint vertexArrays[1];

void
display(void)
{
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(vertexArrays[0]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void init()
{
    static const GLfloat vertices[NumVertices][2] = {
            {-0.5, 0.0},
            {0.5, 0.0},
            {0, -0.5},
    };

	glCreateVertexArrays(1, vertexArrays);

    GLuint buffers[1];
    glCreateBuffers(1, buffers);
	glNamedBufferStorage(buffers[0], sizeof(vertices), vertices, 0);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"},
		{GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glBindVertexArray(vertexArrays[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);
}


int main(int argc, char** argv)
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    glfwMakeContextCurrent(window);

    gl3wInit();
    init();

	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

