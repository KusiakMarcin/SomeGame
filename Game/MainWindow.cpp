//#include "MainWindow.h"
//#include "Logger.h"
//
//
//
//MainWindow::MainWindow(int width, int height, const char* title,GLFWmonitor* monitor, GLFWwindow* share)
//{
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    Window = glfwCreateWindow(width, height, title, NULL, NULL);
//    if (Window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//    }
//
//    glfwMakeContextCurrent(Window);
//    glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
//    glViewport(0, 0, width, height);
//
//    while (!glfwWindowShouldClose(Window))
//    {
//        processInput();
//        glfwSwapBuffers(Window);
//        glfwPollEvents();
//    }
//
//}
//
//
//MainWindow::~MainWindow() {
//    glfwTerminate();
//}
//
//void MainWindow::processInput()
//{
//    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(Window, true);
//}
//
//void MainWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//    
//}
