#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Terrain/Terrain.h"

#include <iostream>

int main() {
    //Init window
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Terraquest");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    //Clock for fps and physics
    sf::Clock deltaClock;
    auto const deltaTime = 1.0f / 20;
	float accumulator = 0.0f;
    ImGui::SFML::Update(window, deltaClock.restart());

    //Camera
    sf::Vector2<float> camera = { 0, 0 };
    bool up = false, down = false, left = false, right = false;
    float xMovement = 0.0, yMovement = 0.0;

    //Terrain
    TerrainNamespace::Terrain terrain(200, 200, 2);

    //Event
    while (window.isOpen()) {
        //Clocks
		auto currentTime = deltaClock.restart().asSeconds();
        accumulator += currentTime;

        //Event proceesing
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                    up = true;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                    down = true;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                    right = true;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                    left = true;
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyReleased->scancode == sf::Keyboard::Scancode::W) {
                    up = false;
                }
                else if (keyReleased->scancode == sf::Keyboard::Scancode::S) {
                    down = false;
                }
                else if (keyReleased->scancode == sf::Keyboard::Scancode::D) {
                    right = false;
                }
                else if (keyReleased->scancode == sf::Keyboard::Scancode::A) {
                    left = false;
                }
            }
            else if (const auto* mouse = event->getIf<sf::Event::MouseWheelScrolled>()) {
                float delta = mouse->delta;
                terrain.setTileSize(terrain.getTileSize() + delta);
            }
        }
        
        //Camera position update
        if (up) {
            if (yMovement > -0.5)
                yMovement -= 0.05;
            else
                yMovement = -0.5;
        }
        if (down) {
            if (yMovement < 0.5)
                yMovement += 0.05;
            else
                yMovement = 0.5;
        }
        if (right) {
            if (xMovement < 0.5)
                xMovement += 0.05;
            else
                xMovement = 0.5;
        }
        if (left) {
            if (xMovement > -0.5)
                xMovement -= 0.05;
            else
                xMovement = -0.5;
        }

        if (!(up || down)) {
            if (yMovement > 0.05)
                yMovement -= 0.05;
            else if (yMovement < -0.05)
                yMovement += 0.05;
            else {
                yMovement = 0;
            }
        }
        if (!(right || left)) {
            if (xMovement > 0.05)
                xMovement -= 0.05;
            else if (xMovement < -0.05)
                xMovement += 0.05;
            else {
                xMovement = 0;
            }
        }
        camera.x += xMovement;
        camera.y += yMovement;
        if (camera.x <= 0.0) camera.x = 0.0, xMovement = 0.0;
        if (camera.y <= 0.0) camera.y = 0.0, yMovement = 0.0;


        while (accumulator >= deltaTime) {
			//Update your game logic here, updates vyks reciau negu frames, dabar 20/sec

            accumulator -= deltaTime;
        }

        //Update graphics
        float fps = (currentTime > 0) ? 1.0f / currentTime : 0.0f;
        //std::cout << "FPS: " << fps << std::endl;
        
        //Terrain
        terrain.draw(window, camera);


        //Display window
        ImGui::SFML::Render(window);
        window.display();
        window.clear();
    }

    ImGui::SFML::Shutdown();
}

