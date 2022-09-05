#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Engine/include/Engine.hpp"
#include <iostream>

int main(int argc, char* args[])
{
    SDL_Event e{};
    bool quit = false;
    GFXManager::Init("Chironi");
    GFXManager::DefaultFont = TTF_OpenFont( "Assets/Roboto-Black.ttf", 72 );

    GFXManager::Add("Hello", "Assets/previewd.png");
    GFXManager::Add("Chiron", "Assets/Chironi.bmp");
    GFXManager::Add("Saul", "Assets/sas.png");
    GFXManager::Add("prev", "Assets/previewd.png");
    GFXManager::Add("testo", GFXManager::CreateTextImage("Testo di prova", {255,255,255,255}));

    Camera camera {"Main"};
    Camera camera2 {"Gui"};

    camera2.CameraRender.x = 0;
    camera2.CameraRender.y = 0;
    
    Player player {"Chiron", 150,150, Vector2{30, 30}, 6};
    GameObject obj {"Hello", 1280,100, Vector2{0, 620}};
    GameObject obj2 {"Hello", 150,150, Vector2{0, 470}};
    GameObject obj3 {"Hello", 150,150, Vector2{150, 320}};

    GameObject obj4 {"testo", 0, 0, Vector2{0, 0}};
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

        SDL_RenderSetViewport(GFXManager::Renderer, &viewPort);
        SDL_RenderCopy(GFXManager::Renderer, GFXManager::Get("prev"), nullptr, nullptr);
        
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

