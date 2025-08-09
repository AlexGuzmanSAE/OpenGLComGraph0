#include "glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "iostream"


Application applicaion;

void check_keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    applicaion.KeyBoard( key, scancode, action, mods);
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
    applicaion.window = glfwCreateWindow(1240, 920, "HelloPlane", NULL, NULL);
    if (!applicaion.window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(applicaion.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error al inicializar GLAD" << std::endl;
        return -1;
    }
    
    
    glfwSetKeyCallback(applicaion.window, check_keyboard);
    applicaion.SetUp();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(applicaion.window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        applicaion.Update();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        applicaion.Draw();
        /* Swap front and back buffers */
        glfwSwapBuffers(applicaion.window);
    }

    glfwTerminate();
    return 0;
}