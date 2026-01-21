#include "Window.h"

Window::Window(int width, int height, const std::string& title)
    : m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr)
{
}

Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
}

bool Window::Init() {
    // 1. Inicjalizacja GLFW
    if (!glfwInit()) {
        std::cerr << "Blad: Nie udalo sie zainicjalizowac GLFW" << std::endl;
        return false;
    }

    // 2. Konfiguracja kontekstu OpenGL (wersja 3.3, Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 3. Tworzenie okna
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr) {
        std::cerr << "Blad: Nie udalo sie utworzyc okna GLFW" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    // 4. £adowanie wskaŸników OpenGL przez GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Blad: Nie udalo sie zainicjalizowac GLAD" << std::endl;
        return false;
    }

    // Konfiguracja Viewportu i Callbacków
    glViewport(0, 0, m_Width, m_Height);
    glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

    // W³¹czenie obs³ugi przezroczystoœci (Alpha Blending)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Window::Update() {
    // Zamiana buforów (Double Buffering)
    glfwSwapBuffers(m_Window);
    // Obs³uga zdarzeñ systemowych (klawiatura, mysz, zamkniêcie)
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}