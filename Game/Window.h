#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Window {
public:
    // Konstruktor i Destruktor
    Window(int width, int height, const std::string& title);
    ~Window();

    // Inicjalizacja bibliotek i tworzenie okna
    bool Init();

    // Obs³uga pêtli okna (swap buffers, poll events)
    void Update();

    // Sprawdza czy okno powinno siê zamkn¹æ
    bool ShouldClose() const;

    // Pobieranie surowego wskaŸnika GLFW (przydatne dla InputManagera w main.cpp)
    GLFWwindow* GetNativeWindow() const { return m_Window; }

    // Gettery rozmiaru
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

private:
    GLFWwindow* m_Window;
    int m_Width;
    int m_Height;
    std::string m_Title;

    // Callback do zmiany rozmiaru okna
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif
