#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <fstream>
#include <sstream>
#include "Phisics.h"
#include <iostream>

// WskaŸniki na obiekty gry
SpriteRenderer* Renderer;
Player* PlayerOne;
Phisics* GamePhisics;

unsigned int Game::UnitsIDs = 1;



Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height),FrameRate(60.0f), LeftMouseButton(false)
{
    projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    CameraPosition = glm::vec2(0.0f,0.0f);
}

Game::~Game()
{
    delete Renderer;
    delete PlayerOne;
}

void Game::Init()
{
    // 1. £adowanie shaderów
    // U¿ywamy standardowego shadera sprite (zak³adamy, ¿e obs³uguje uniform 'spriteColor')
    ResourceManager::LoadShader("Player.vrtx", "Player.frag", nullptr, "Player");

    // 2. Konfiguracja macierzy projekcji (Dopasowanie do wymiarów okna)
    
    
   
   
    ResourceManager::GetShader("Player").SetMatrix4("projection", projection);

    // 3. Inicjalizacja Renderera
    Shader tmp = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(tmp);


    // 4. £adowanie tekstur
    // U¿ywamy tekstury 'block.png' jako bazowego bia³ego kwadratu dla wszystkich obiektów
    

    // 5. Konfiguracja Gracza
    glm::vec2 playerPos = glm::vec2(100.0f, 410.0f); // Startowa pozycja w powietrzu
    glm::vec2 playerSize = glm::vec2(30.0f, 80.0f);  // Rozmiar gracza
    glm::vec3 playerColor = glm::vec3(1.0f, 0.0f, 0.0f); // Czerwony kolor gracza

    // Tworzymy obiekt gracza
    PlayerOne = new Player(playerPos, playerSize, ResourceManager::GetTexture("PlayerAnimation"), playerColor);
    LoadLevel("Levels/test.txt");
    
    float velocityX = 1500.0f * glm::cos(PlayerOne->FireAngle);
    float velocityY = 1500.0f * glm::sin(PlayerOne->FireAngle);
    Projectile newProjectile(PlayerOne->ID, PlayerOne->Position + glm::vec2(20.0f, -50.0f),
        glm::vec2(20.0f, 10.0f),
        glm::vec2(velocityX, velocityY),
        30000.0f, glm::degrees(PlayerOne->FireAngle));
    
    ProjectileObjectList.push_back(newProjectile);
    
    
}

void Game::Update(float dt, double mousePositionX, double mousePositionY)
{
    // Definiujemy wysokoœæ gruntu (taka sama jak w Render)
    float groundHeight = 100.0f;

    // Obliczamy "efektywn¹" wysokoœæ ekranu dla fizyki gracza.
    // Gracz ma myœleæ, ¿e pod³oga jest wy¿ej, na szczycie naszego gruntu.
    float effectiveHeight = this->Height - groundHeight;
    PlayerOne->CrossHairPosition = glm::vec2(mousePositionX, mousePositionY);
    CameraPosition = -PlayerOne->Position;

    // Aktualizujemy fizykê gracza (ruch, grawitacja)
    
    
    CheckPlayerTerrainColisions();
    
    CheckProjectileColisions();

    for (int Object = 0; Object < ProjectileObjectList.size(); Object++)
    {
        ProjectileObjectList[Object].Update(dt);
       
        if (ProjectileObjectList[Object].FireRange <= 0.0f)
            ProjectileObjectList.erase(ProjectileObjectList.begin() + Object);
    
    }

    PlayerOne->Update(dt);

    
    
    
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        // Domyœlnie brak ruchu poziomego (hamowanie)
        PlayerOne->ProcessKeyboard(NONE, dt);

        // Sterowanie
        /*if(this->Keys[GLFW_KEY_ESCAPE])
            Menu*/
        if (this->Keys[GLFW_KEY_A])
            PlayerOne->ProcessKeyboard(LEFT, dt);
        if (this->Keys[GLFW_KEY_D])
            PlayerOne->ProcessKeyboard(RIGHT, dt);
        if (this->Keys[GLFW_KEY_SPACE])
            PlayerOne->Jump();
        if (this->LeftMouseButton && !(PlayerOne->IsFiring>0)) {
            
            ProjectileObjectList.push_back(PlayerOne->Shoot());
        }
    }
}

void Game::Render(float frame)
{ 
    if (this->State == GAME_ACTIVE)
    {
        // 1. Rysowanie T³a (Opcjonalnie - np. b³êkitne niebo)
        
        // 2. Rysowanie terenu
       


        for (int Object = 0; Object < TerrainObjectsList.size(); Object++)
        {
            TerrainObjectsList[Object].Draw(*Renderer,
                ResourceManager::GetTexture("Dirt"),
                ResourceManager::GetShader("Terrain"),
                projection, CameraPosition);
        }

        for (int Object = 0; Object < ProjectileObjectList.size(); Object++)
        {
            ProjectileObjectList[Object].Draw(*Renderer,
                ResourceManager::GetTexture("Projectile"),
                ResourceManager::GetShader("Sprite"),
                projection, CameraPosition);
        }
        
        
        
        
        // Rysowanie Gracza


        if (PlayerOne->IsMoving && PlayerOne->IsGrounded)
        {

            PlayerOne->DrawAnimation(*Renderer,
                ResourceManager::GetTexture("PlayerAnimation"),
                ResourceManager::GetShader("SpriteAnimation"),
                projection);
            PlayerOne->DrawGun(*Renderer,
                ResourceManager::GetTexture("Rifle"),
                ResourceManager::GetShader("Sprite"),
                projection);
            PlayerOne->DrawCrossHair(* Renderer,
                ResourceManager::GetTexture("CrossHair"),
                ResourceManager::GetShader("Sprite"),
                projection);
        }
        else
        {
            PlayerOne->DrawIdle(*Renderer,
                ResourceManager::GetTexture("PlayerIdle"),
                ResourceManager::GetShader("Sprite"),
                projection);
            PlayerOne->DrawGun(*Renderer,
                ResourceManager::GetTexture("Rifle"),
                ResourceManager::GetShader("Sprite"),
                projection);
            PlayerOne->DrawCrossHair(*Renderer,
                ResourceManager::GetTexture("CrossHair"),
                ResourceManager::GetShader("Sprite"),
                projection);
        }
    }

   
}





void Game::LoadLevel(const char* LevelFile)
{
    std::ifstream file(LevelFile);

    if(file.is_open()&&file.good())
    {   
        std::string text;
        

        while(std::getline(file,text))
        {
            if (text.empty() || text[0] == '#')
                continue;
            float x, y, width, height;
            std::stringstream s(text);
            s >> x >> y >> width >> height;
            std::cout << s.str() << std::endl;
              
            glm::vec2 size(width, height);
            glm::vec2 position(x, y);
            Terrain tmp(position, size);
            TerrainObjectsList.push_back(tmp);
            std::cout << TerrainObjectsList.back().Position.x<<TerrainObjectsList.back().Position.y << std::endl;
        }
    }

    


}


void Game::CheckPlayerTerrainColisions()
{


    for (int Object = 0; Object < TerrainObjectsList.size(); Object++)
    {

        if (GamePhisics->CheckColision(*PlayerOne, TerrainObjectsList[Object]))
        {
            GamePhisics->ResolveColision(*PlayerOne, TerrainObjectsList[Object]);

        }


    }

}

void Game::CheckProjectileColisions()
{
    for(int ObjectP = 0; ObjectP< ProjectileObjectList.size(); ObjectP++)
    {
        for (int ObjectT = 0; ObjectT < TerrainObjectsList.size(); ObjectT++)
        {
               
                if(GamePhisics->CheckColision(ProjectileObjectList[ObjectP],TerrainObjectsList[ObjectT]))
                {
                    GamePhisics->ResolveColision(ProjectileObjectList[ObjectP], TerrainObjectsList[ObjectT]);
                    ProjectileObjectList.erase(ProjectileObjectList.begin() + ObjectP);

                    break;
                        

                }
        
        }
    
    }

}