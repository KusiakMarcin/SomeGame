#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <fstream>
#include <sstream>
#include "Phisics.h"
#include <iostream>
#include "Menu.h"


// Wskaüniki na obiekty gry
SpriteRenderer* Renderer;
Player* PlayerOne;
Phisics* GamePhisics;
Interface GameInterface;
TextRenderer* Text;
Menu GameMenu;



Game::Game(unsigned int width, unsigned int height)
    : State(GAME_MENU), Keys(), Width(width), Height(height),FrameRate(60.0f), LeftMouseButton(false)
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
  

    
    
    GameInterface = Interface();
   
    ResourceManager::GetShader("Player").SetMatrix4("projection", projection);
    ResourceManager::LoadTexture("Assets/White.png", true, "White");
    // 3. Inicjalizacja Renderera
    Shader tmp = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(tmp);
    
    Text = new TextRenderer(Width, Height);
    Text->Load("Assets/Arial.ttf", 40);
    GameMenu.AddItem(
        { 300, 250 }, { 200, 60 }, "GRAJ",
        [this]() { LoadLevel("Levels/test3.txt"); }
    );

    GameMenu.AddItem(
        { 300, 330 }, { 200, 60 }, "WYJSCIE",
        [this]() { State = GAME_EXIT; }
    );
  

    
   
    //LoadLevel("Levels/test3.txt");

    // Tworzymy obiekt gracza
    
   
    
    
}
void Game::Menu()
{
    GameMenu.Draw(*Renderer, *Text, this->projection);
}
void Game::Update(float dt, double mousePositionX, double mousePositionY)
{
    
    PlayerOne->CrossHairPosition = glm::vec2(mousePositionX, mousePositionY);
    CameraPosition = -PlayerOne->Position;

    
    
    
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

        UnitObjectsList[Object]->Update(dt, *PlayerOne);
        if (UnitObjectsList[Object]->IsKilled) {
            //std::cout << "erase" << std::endl;
            UnitObjectsList.erase(UnitObjectsList.begin() + Object);
            continue;
        }
        if (UnitObjectsList[Object]->PlayerDetected)
        {
            if (UnitObjectsList[Object]->ClassEnemy == "Sentry"&& UnitObjectsList[Object]->FireCooldown<=0.0f)
                ProjectileObjectsList.push_back(UnitObjectsList[Object]->Shoot());
            else UnitObjectsList[Object]->Atack();

        }
        if (UnitObjectsList[Object]->HP < 1) {
            //std::cout << "death" << std::endl;
            UnitObjectsList[Object]->Death();
            
        }
           
      

    }

    PlayerOne->Update(dt);
    if (PlayerOne->IsKilled) {
        this->State = GAME_OVER;
        GameOverClear();


    }

    
    
    
}

void Game::ProcessInput(float dt)
{
    if (State == GAME_MENU)
    {
        // Przekazujemy sterowanie do menu
        if (this->Keys[GLFW_KEY_W])
            GameMenu.SelectPrev();

        if (this->Keys[GLFW_KEY_S])
            GameMenu.SelectNext();

        if (this->Keys[GLFW_KEY_ENTER])
        {
            GameMenu.ExecuteSelected();
            this->State= GAME_ACTIVE;
        }
        return;
    }
    if (State == GAME_OVER)
    {
        
        if (this->Keys[GLFW_KEY_ENTER])
        {
            
            this->State = GAME_MENU;
        }
        return;
    }
    if (this->State == GAME_ACTIVE)
    {
        // Domyúlnie brak ruchu poziomego (hamowanie)
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
            /*std::cout << "Shoot()"<< ProjectileObjectsList.back().Position.x <<"," 
                << ProjectileObjectsList.back().FireRange << std::endl;*/
        }
    }
}

void Game::Render(float frame)
{ 
   
    if (this->State == GAME_OVER){
        Texture2D tmp = ResourceManager::GetTexture("GameOver");
        Renderer->GameOver(tmp,ResourceManager::GetShader("GameOver"));
    }
    if(this->State ==GAME_ACTIVE){
        // 1. Rysowanie T≥a (Opcjonalnie - np. b≥Íkitne niebo)
        
        
        Texture2D tmp = ResourceManager::GetTexture("Heart");
        GameInterface.DrawHUD(*Renderer, ResourceManager::GetShader("Sprite"),
             *PlayerOne,tmp , projection);

        for (int Object = 0; Object < TerrainObjectsList.size(); Object++)
        {
            TerrainObjectsList[Object].Draw(*Renderer,
                ResourceManager::GetTexture(TerrainObjectsList[Object].TerrainClass),
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
        
       
        for (int i = 0; i < UnitObjectsList.size(); i++)
        {
            auto& unit = UnitObjectsList[i];

            // Pobieramy teksturÍ na podstawie nazwy klasy (np. "Crawler", "Flyer", "Sentry")
            Texture2D texture = ResourceManager::GetTexture(unit->ClassEnemy);
            

            if (unit->ClassEnemy == "Sentry")
            {
                
               
                unit->DrawGun(*Renderer, ResourceManager::GetTexture("Canon"), ResourceManager::GetShader("Sprite"), projection, CameraPosition);
                
                unit->Draw(*Renderer, ResourceManager::GetTexture("Sentry"), ResourceManager::GetShader("Sprite"), projection, CameraPosition);

               
            }
            else
            {
                 //Reszta (Crawler, Flyer) korzysta z animacji
                unit->DrawAnimation(*Renderer, texture, ResourceManager::GetShader("SpriteAnimation"), projection, CameraPosition);
            }
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
            std::stringstream s(text);
            char ctrl;
            s >> ctrl;
            switch (ctrl) {
            case 'P':
                float x, y;
                s >> x >> y;
                glm::vec2 size(30.0f, 80.0f);
                glm::vec2 position(x, y);
                glm::vec3 playerColor = glm::vec3(1.0f, 1.0f, 1.0f);
                PlayerOne = new Player(position, size, ResourceManager::GetTexture("PlayerAnimation"), playerColor);
                break;
            case 'D':
            {
                float x, y, width, height;

                s >> x >> y >> width >> height;
                //std::cout << s.str() << std::endl;

                glm::vec2 size(width, height);
                glm::vec2 position(x, y);
                
                Terrain tmp(position, size,"Dirt");
                TerrainObjectsList.push_back(tmp);
                //std::cout << TerrainObjectsList.back().Position.x << TerrainObjectsList.back().Position.y << std::endl;
                break;
            }
            case 'W':
            {
                float x, y, width, height;

                s >> x >> y >> width >> height;
                //std::cout << s.str() << std::endl;

                glm::vec2 size(width, height);
                glm::vec2 position(x, y);

                Terrain tmp(position, size, "Wood");
                TerrainObjectsList.push_back(tmp);
                //std::cout << TerrainObjectsList.back().Position.x << TerrainObjectsList.back().Position.y << std::endl;
                break;
            }
            case 'M':
            {
                float x, y, width, height;

                s >> x >> y >> width >> height;
                //std::cout << s.str() << std::endl;

                glm::vec2 size(width, height);
                glm::vec2 position(x, y);

                Terrain tmp(position, size, "Magma");
                TerrainObjectsList.push_back(tmp);
                //std::cout << TerrainObjectsList.back().Position.x << TerrainObjectsList.back().Position.y << std::endl;
                break;
            }
            case 'C':
            {
                int id;
                float x, y;
                s >> id >> x >> y;
                glm::vec2 size(60.0f, 40.0f);
                glm::vec2 position(x, y);
                glm::vec2 hitbox(15.0f, 10.0f);
                UnitObjectsList.push_back(std::make_unique<Crawler>(id, position, size,hitbox));

                break;
            }
            case 'F':
            {
                int id;
                float x, y;
                s >> id >> x >> y;
                glm::vec2 size(60.0f, 30.0f);
                glm::vec2 position(x, y);
                glm::vec2 hitbox(10.0f, 15.0f);
                UnitObjectsList.push_back(std::make_unique<Flyer>(id, position, size, hitbox));

                break;
            }
             case 'S':
            {
                int id;
                float x, y;
                s >> id >> x >> y;
                glm::vec2 size(40.0f, 40.0f);
                glm::vec2 position(x, y);
                glm::vec2 hitbox(0.0f, 0.0f);
                UnitObjectsList.push_back(std::make_unique<Sentry>(id, position, size, hitbox));

                break;
            }

            }
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
            if(TerrainObjectsList[Object].isHarmful) PlayerOne->Hit();

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
                    if (TerrainObjectsList[ObjectT].isDestructable) {

                        TerrainObjectsList.erase(TerrainObjectsList.begin() + ObjectT);
                    }
                    
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
                ProjectileObjectsList.erase(ProjectileObjectsList.begin() + ObjectT);


            }

        }

    }
    for (int ObjectT = 0; ObjectT < ProjectileObjectsList.size(); ObjectT++)
    {

        if (GamePhisics->CheckColision(ProjectileObjectsList[ObjectT], *PlayerOne))
        {

            if (ProjectileObjectsList[ObjectT].SourceID != 1) { 
                
                PlayerOne->Hit();
                ProjectileObjectsList.erase(ProjectileObjectsList.begin() + ObjectT);
            }
            


        }

    }

}


void Game::GameOverClear()
{


    for (int Object = ProjectileObjectsList.size()-1; Object >-1; Object--)
    {
        ProjectileObjectsList.erase(ProjectileObjectsList.begin() + Object);

       

    }
    for (int Object = TerrainObjectsList.size()-1; Object > -1; Object--)
    {
        TerrainObjectsList.erase(TerrainObjectsList.begin() + Object);



    }
    for (int Object = UnitObjectsList.size()-1; Object > -1; Object--)
    {
        UnitObjectsList.erase(UnitObjectsList.begin() + Object);



    }
    delete PlayerOne;

}