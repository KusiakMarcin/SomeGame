#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"

#include <iostream>
/*
    1.bufory vertex array, buffer. dla elemetnu Element buffer(glGenBuffers glGenVertexArrays)
    2.bind buffer jesli chcesz robic rzeczy na buforze
    3.VertexAtributePointer ustala layout w tablicy, kazdy atrybut pojedynczo

*/
// Konfiguracja okna
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Callbacki
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void LoadShaders();
void LoadTextures();
// Inicjalizacja obiektu Gry - zmieniliœmy nazwê z Breakout na Platformer dla czytelnoœci
Game Platformer(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    // 1. Konfiguracja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Tworzenie Okna - zmieniony tytu³
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Platformer Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Rejestracja callbacków
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // 3. £adowanie GLAD (wskaŸniki funkcji OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Konfiguracja globalna OpenGL
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    

    // 4. Inicjalizacja Gry (wczytanie shaderów, tekstur, utworzenie gracza)
    Platformer.Init();

    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    
    LoadShaders();
    LoadTextures();


    
    

    
   
    
    glClearColor(0.7f,0.6f,0.83f,1.0);
    while (!glfwWindowShouldClose(window))
    {
        // Obliczanie czasu klatki
        glClear(GL_COLOR_BUFFER_BIT);
        float currentFrame = glfwGetTime();
        
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        glfwPollEvents();
        
        Platformer.ProcessInput(deltaTime);
        
        Platformer.Update(deltaTime);
        Platformer.Render();
        
        
       
        /*float timePassed = glfwGetTime() - currentFrame;
        while(timePassed >= 1.0f/Platformer.FrameRate)
        {
            timePassed = glfwGetTime() - currentFrame;
        }*/
        glfwSwapBuffers(window);
    }

    // Sprz¹tanie
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

// Callback zmiany klawiszy - aktualizuje tablicê Keys w obiekcie Game
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Wyjœcie z gry pod ESC
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Aktualizacja stanu klawiszy w obiekcie Game
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Platformer.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Platformer.Keys[key] = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void LoadShaders()
{

    ResourceManager::LoadShader("PlayerAnimation.vrtx","PlayerAnimation.frag",nullptr,"PlayerAnimation");
    ResourceManager::LoadShader("Player.vrtx", "Player.frag", nullptr, "Player");
    ResourceManager::LoadShader("Terrain.vrtx", "Terrain.frag", nullptr, "Terrain");
}

void LoadTextures()
{
    
    ResourceManager::LoadTexture("Assets/dirt.png",true, "Dirt");
    ResourceManager::LoadTexture("Assets/PlayerAnimation.png",true, "PlayerAnimation");
    ResourceManager::LoadTexture("Assets/PlayerIdle.png", true, "PlayerIdle");
    ResourceManager::LoadTexture("Assets/Rifle.png",true, "Rifle");
    
    
}