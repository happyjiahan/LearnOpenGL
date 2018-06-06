#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


void
display(void)
{
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
//    glClearBufferfv(GL_COLOR, 0, black);
}

void init()
{
    static const GLfloat vertices[3][2] = {
            {-0.9, -0.9},
            {0.85, -0.9},
            {-0.9, -0.85}
    };

    GLuint buffers[1];
    glCreateBuffers(1, buffers);
    std::cout << "buffers: " << buffers << std::endl;
}


int main(int argc, char** argv)
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    glfwMakeContextCurrent(window);

    gl3wInit();
    init();

    display();
}

