#include "glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "iostream"


Application application;

void check_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    application.KeyBoard( key, scancode, action, mods);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwWindowShouldClose(window);
    }
}

int main(void)
{
   
    /* Initialize the library */
    if (!glfwInit())    
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    application.window = glfwCreateWindow(1020, 720, "HelloTriangle", NULL, NULL);
    if (!application.window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(application.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error al inicializar GLAD" << std::endl;
        return -1;
    }
    
    
    glfwSetKeyCallback(application.window, check_keyboard);
    application.SetUp();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(application.window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        application.Update();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        application.Draw();
        /* Swap front and back buffers */
        glfwSwapBuffers(application.window);
    }

    glfwTerminate();
    return 0;
}