#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include <iostream>

// Wskaüniki na obiekty gry
SpriteRenderer* Renderer;
Player* PlayerOne;
Terrain* g;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height),FrameRate(60.0f)
{
    projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
}

Game::~Game()
{
    delete Renderer;
    delete PlayerOne;
}

void Game::Init()
{
    // 1. £adowanie shaderÛw
    // Uøywamy standardowego shadera sprite (zak≥adamy, øe obs≥uguje uniform 'spriteColor')
    ResourceManager::LoadShader("Player.vrtx", "Player.frag", nullptr, "Player");

    // 2. Konfiguracja macierzy projekcji (Dopasowanie do wymiarÛw okna)
    

   
   
    ResourceManager::GetShader("Player").SetMatrix4("projection", projection);

    // 3. Inicjalizacja Renderera
    Shader tmp = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(tmp);

    // 4. £adowanie tekstur
    // Uøywamy tekstury 'block.png' jako bazowego bia≥ego kwadratu dla wszystkich obiektÛw
    

    // 5. Konfiguracja Gracza
    glm::vec2 playerPos = glm::vec2(50.0f, 50.0f); // Startowa pozycja w powietrzu
    glm::vec2 playerSize = glm::vec2(100.0f, 100.0f);  // Rozmiar gracza
    glm::vec3 playerColor = glm::vec3(1.0f, 0.0f, 0.0f); // Czerwony kolor gracza

    // Tworzymy obiekt gracza
    PlayerOne = new Player(playerPos, playerSize, ResourceManager::GetTexture("PlayerAnimation"), playerColor);
    glm::vec2 GroundPosition = glm::vec2(0.0f, Height - 100.0f);
    glm::vec2 GroundSize = glm::vec2(Width, 100.0f);
    Terrain Ground(GroundPosition, GroundSize);
    TerrainObjectsList.push_back(Ground);
    g = &Ground;
}

void Game::Update(float dt)
{
    // Definiujemy wysokoúÊ gruntu (taka sama jak w Render)
    float groundHeight = 100.0f;

    // Obliczamy "efektywnπ" wysokoúÊ ekranu dla fizyki gracza.
    // Gracz ma myúleÊ, øe pod≥oga jest wyøej, na szczycie naszego gruntu.
    float effectiveHeight = this->Height - groundHeight;

    // Aktualizujemy fizykÍ gracza (ruch, grawitacja)
    PlayerOne->Update(dt, effectiveHeight);
    
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        // Domyúlnie brak ruchu poziomego (hamowanie)
        PlayerOne->ProcessKeyboard(NONE, dt);

        // Sterowanie
        if (this->Keys[GLFW_KEY_A])
            PlayerOne->ProcessKeyboard(LEFT, dt);
        if (this->Keys[GLFW_KEY_D])
            PlayerOne->ProcessKeyboard(RIGHT, dt);
        if (this->Keys[GLFW_KEY_SPACE])
            PlayerOne->Jump();
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // 1. Rysowanie T≥a (Opcjonalnie - np. b≥Íkitne niebo)
        // Renderer->DrawSprite(ResourceManager::GetTexture("block"), glm::vec2(0,0), glm::vec2(this->Width, this->Height), 0.0f, glm::vec3(0.5f, 0.8f, 1.0f));

        // 2. Rysowanie Gruntu
        float groundHeight = 100.0f;
        
      
       
        TerrainObjectsList[0].Draw(*Renderer,
            ResourceManager::GetTexture("Dirt") ,
            ResourceManager::GetShader("Terrain"),
            projection);
        
        // 3. Rysowanie Gracza
        

        if(PlayerOne->IsMoving&&PlayerOne->IsGrounded)
            PlayerOne->Draw(*Renderer, 
                ResourceManager::GetTexture("PlayerAnimation"),
                ResourceManager::GetShader("Player"),
                projection);
        else 
        
        PlayerOne->Draw(*Renderer,
            ResourceManager::GetTexture("PlayerIdle"),
            ResourceManager::GetShader("Player"),
            projection);
    }
}