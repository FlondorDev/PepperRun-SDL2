#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Engine/include/Engine.hpp"

#include "../include/Player.hpp"
#include "../include/Pepper.hpp"
#include "../include/Wall.hpp"

int main(int argc, char *args[])
{
    SDL_Event e{};
    bool quit = false;
    GFXManager::Init("Chironi");
    GFXManager::DefaultFont = TTF_OpenFont("../Assets/Roboto-Black.ttf", 72);

    GFXManager::Add("Cobble", "../Assets/Cobble.png");
    GFXManager::Add("Player", "../Assets/Player.png");
    GFXManager::Add("Pepper", "../Assets/Pepper.png");
    GFXManager::Add("Wall", "../Assets/Wall.png");
    GFXManager::Add("testo", GFXManager::CreateTextImage("Pepper Run", {255, 255, 255, 255}));

    Camera camera{"Main"};
    Camera camera2{"Gui"};

    Player player{"Player", Vector2{30, 30}, 6, 64, 64};
    Pepper pepper{"Pepper", Vector2{256, 410}};
    Wall obj{"Cobble", Vector2{0, 620}};
    Wall obj2{"Cobble", Vector2{0, 470}, (64 * 10), 64};
    Wall obj3{"Cobble", Vector2{150, 320}};

    GameObject obj4{"testo", Vector2{0, 0}};

    CameraManager::Get("Gui")->SetTarget(&obj4);

    std::string Title;
    SDL_Rect viewPort = {GFXManager::LogicWidth - 64 - 128, 64, 128, 128};

    while (!quit)
    {
        Clock::StartTick();
        // Clear screen
        SDL_RenderClear(GFXManager::Renderer);
        SDL_RenderSetViewport(GFXManager::Renderer, nullptr);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        ControllerManager::Input(SDL_GetKeyboardState(nullptr));

        UpdateManager::Update();

        PhysicsManager::Update();

        CameraManager::Update();

        SDL_RenderCopy(GFXManager::Renderer, GFXManager::Get("Wall"), nullptr, nullptr);

        DrawManager::Draw();

        PhysicsManager::Draw();

        // Minimap
        // SDL_RenderSetViewport(GFXManager::Renderer, &viewPort);
        // SDL_RenderCopy(GFXManager::Renderer, GFXManager::Get("Wall"), nullptr, nullptr);

        // Update screen
        SDL_SetRenderDrawColor(GFXManager::Renderer, 0, 0, 0, 255);
        SDL_RenderPresent(GFXManager::Renderer);

        Title = "Current FPS: " + std::to_string(Clock::GetFps()) + " Current DeltaTime: " + std::to_string(Clock::GetDeltaTime());
        SDL_SetWindowTitle(GFXManager::Window, Title.c_str());

        Clock::EndTick();
    }

    ControllerManager::Clear();
    UpdateManager::Clear();
    PhysicsManager::Clear();
    DrawManager::Clear();
    GFXManager::Close();
    return 0;
}

int WinMain(int argc, char *args[])
{
    return main(argc, args);
}
