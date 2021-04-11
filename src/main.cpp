#include <iostream>
#include <assert.h>
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>
int main(int argc, char **argv)
{

    if (!glfwInit())
    {
        printf("problem with GLFW\n");
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(640, 360, "Starter Project", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 640, 360);
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(1.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("Yeah !!!! \n");
    return 0;
}