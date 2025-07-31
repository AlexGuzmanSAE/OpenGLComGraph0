#include "GLFW/glfw3.h"
#include "Application.h"

Application applicaion;

void check_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        //activar flag de la salida del programa
        glfwSetWindowShouldClose(window, 1);
    }
}



int main(void)
{
    GLFWwindow* window;
        
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "HelloApplication", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    applicaion.SetUp();

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, check_keyboard);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);
        applicaion.Update();
        /* Swap front and back buffers */
        //glfwSwapBuffers(window);
        applicaion.Draw();
        /* Poll for and process events */
        //glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}