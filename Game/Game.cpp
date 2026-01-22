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
    
    ResourceManager::LoadShader("Player.vrtx", "Player.frag", nullptr, "Player");

    // 2. Konfiguracja macierzy projekcji 
    
    
   
   
    ResourceManager::GetShader("Player").SetMatrix4("projection", projection);

    // 3. Inicjalizacja Renderera
    Shader tmp = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(tmp);


  

    UnitObjectsList.push_back(std::make_unique<Crawler>(2, glm::vec2(100.0f, 300.0f), glm::vec2(50.0f, 30.0f),
        glm::vec2(50.0f, 30.0f)));
    // 5. Konfiguracja Gracza
    glm::vec2 playerPos = glm::vec2(100.0f, 380.0f); // Startowa pozycja w powietrzu
    glm::vec2 playerSize = glm::vec2(30.0f, 80.0f);  // Rozmiar gracza
    glm::vec3 playerColor = glm::vec3(1.0f, 1.0f, 1.0f); 

    // Tworzymy obiekt gracza
    PlayerOne = new Player(playerPos, playerSize, ResourceManager::GetTexture("PlayerAnimation"), playerColor);
    LoadLevel("Levels/test.txt");
    
    
  
    
}

void Game::Update(float dt, double mousePositionX, double mousePositionY)
{
    
    PlayerOne->CrossHairPosition = glm::vec2(mousePositionX, mousePositionY);
    CameraPosition = -PlayerOne->Position;

    // Aktualizujemy fizykê gracza (ruch, grawitacja)
    
    
    CheckPlayerTerrainColisions();
    
    CheckProjectileColisions();

    CheckUnitTerrainColisions();

    CheckUnitProjectileColisions();

    CheckPlayerUnitColisions();

    for (int Object = 0; Object < ProjectileObjectsList.size(); Object++)
    {
        ProjectileObjectsList[Object].Update(dt);
        
        if (ProjectileObjectsList[Object].FireRange <= 0.0f)
            ProjectileObjectsList.erase(ProjectileObjectsList.begin() + Object);
    
    }

    for (int Object = 0; Object < UnitObjectsList.size(); Object++)
    {

        UnitObjectsList[Object]->Update(dt);
        if (UnitObjectsList[Object]->IsKilled) {
            std::cout << "erase" << std::endl;
            UnitObjectsList.erase(UnitObjectsList.begin() + Object);
            continue;
        }
        if (UnitObjectsList[Object]->HP < 1) {
            std::cout << "death" << std::endl;
            UnitObjectsList[Object]->Death();
            
        }
           
      

    }

    PlayerOne->Update(dt);
    if (PlayerOne->IsKilled) {
        //GameOver();
    }

    
    
    
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
            
            ProjectileObjectsList.push_back(PlayerOne->Shoot());
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

        for (int Object = 0; Object < ProjectileObjectsList.size(); Object++)
        {
            ProjectileObjectsList[Object].Draw(*Renderer,
                ResourceManager::GetTexture("Projectile"),
                ResourceManager::GetShader("Sprite"),
                projection, CameraPosition);
        }
        
        for (int Object = 0; Object < UnitObjectsList.size(); Object++)
        {
            UnitObjectsList[Object]->DrawAnimation(*Renderer,
                ResourceManager::GetTexture("Crawler"),
                ResourceManager::GetShader("SpriteAnimation"),
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

void Game::CheckPlayerUnitColisions()
{


    for (int Object = 0; Object < UnitObjectsList.size(); Object++)
    {

        if (GamePhisics->CheckColision(*PlayerOne, *UnitObjectsList[Object].get()))
        {
            GamePhisics->ResolveColision(PlayerOne, *UnitObjectsList[Object].get());

        }


    }

}

void Game::CheckProjectileColisions()
{
    for(int ObjectP = 0; ObjectP< ProjectileObjectsList.size(); ObjectP++)
    {
        for (int ObjectT = 0; ObjectT < TerrainObjectsList.size(); ObjectT++)
        {
               
                if(GamePhisics->CheckColision(ProjectileObjectsList[ObjectP],TerrainObjectsList[ObjectT]))
                {
                    //std::cout << "colision" << std::endl;
                    GamePhisics->ResolveColision(ProjectileObjectsList[ObjectP], TerrainObjectsList[ObjectT]);
                    ProjectileObjectsList.erase(ProjectileObjectsList.begin() + ObjectP);

                    break;
                        

                }
        
        }
    
    }

}

void Game::CheckUnitTerrainColisions()
{

    
        for (int ObjectP = 0; ObjectP < UnitObjectsList.size(); ObjectP++)
        {
            for (int ObjectT = 0; ObjectT < TerrainObjectsList.size(); ObjectT++)
            {
               
                if (GamePhisics->CheckColision(UnitObjectsList[ObjectP].get(), TerrainObjectsList[ObjectT]))
                {
                    
                    GamePhisics->ResolveColision(UnitObjectsList[ObjectP].get(), TerrainObjectsList[ObjectT]);
                    


                }

            }

        }

    



}
void Game::CheckUnitProjectileColisions()
{

    for (int ObjectP = 0; ObjectP < UnitObjectsList.size(); ObjectP++)
    {
        for (int ObjectT = 0; ObjectT < ProjectileObjectsList.size(); ObjectT++)
        {
           
            if (GamePhisics->CheckColision(ProjectileObjectsList[ObjectT],UnitObjectsList[ObjectP].get()))
            {

                GamePhisics->ResolveColision( ProjectileObjectsList[ObjectT],UnitObjectsList[ObjectP].get());
                ProjectileObjectsList.erase(ProjectileObjectsList.begin() + ObjectP);


            }

        }

    }
}


