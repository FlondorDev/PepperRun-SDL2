#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Engine/include/Engine.hpp"

int main(int argc, char* args[])
{
    SDL_Event e{};
    bool quit = false;
    GFXManager::Init("Chironi");
    GFXManager::DefaultFont = TTF_OpenFont( "Assets/Roboto-Black.ttf", 72 );

    GFXManager::Add("Cobble", "./Assets/Cobble.png");
    GFXManager::Add("Player", "./Assets/Player.png");
    GFXManager::Add("Wall", "./Assets/Wall.png");
    GFXManager::Add("testo", GFXManager::CreateTextImage("Pepper Run", {255,255,255,255}));

    Camera camera {"Main"};
    Camera camera2 {"Gui"};

    camera2.CameraRender.x = 0;
    camera2.CameraRender.y = 0;
    
    Player player {"Player", Vector2{30, 30}, 6, 64, 64};
    GameObject obj {"Cobble",Vector2{0, 620}};
    GameObject obj2 {"Cobble", Vector2{0, 470}, (64*10), 64};
    GameObject obj3 {"Cobble", Vector2{150, 320}};

    GameObject obj4 {"testo", Vector2{0, 0}};
    obj4.rb.DestroyCollider();

    CameraManager::Get("Gui")->SetTarget(&obj4);

    std::string Title;
    SDL_Rect viewPort = { GFXManager::LogicWidth - 64 - 128 , 64, 128, 128 };

    while (!quit) {
        //Clear screen
        SDL_RenderClear( GFXManager::Renderer );
        SDL_RenderSetViewport(GFXManager::Renderer, nullptr);

        Clock::StartTick();

        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        ControllerManager::Input(SDL_GetKeyboardState(nullptr));

        UpdateManager::Update();
        
        PhysicsManager::Update();

        CameraManager::Update();
        
        //SDL_RenderCopy(GFXManager::Renderer, GFXManager::Get("Saul"), &camera.CameraRender, nullptr);
        DrawManager::Draw();

        PhysicsManager::Draw();

        // Minimap
        SDL_RenderSetViewport(GFXManager::Renderer, &viewPort);
        SDL_RenderCopy(GFXManager::Renderer, GFXManager::Get("Wall"), nullptr, nullptr);
        
        //Update screen
        SDL_RenderPresent( GFXManager::Renderer );

        Clock::EndTick();
        Title = "Current FPS: " + std::to_string(Clock::GetFps()) + " Current DeltaTime: " + std::to_string(Clock::GetDeltaTime());
        SDL_SetWindowTitle(GFXManager::Window, Title.c_str());
 
    }

    ControllerManager::Clear();
    UpdateManager::Clear();
    PhysicsManager::Clear();
    DrawManager::Clear();
    GFXManager::Close();
    return 0;
}

int WinMain(int argc, char* args[]){
    return main(argc, args);
}

