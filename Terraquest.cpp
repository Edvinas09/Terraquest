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
    sf::Vector2<int> camera = { 0, 0 };

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
                if (keyPressed->scancode == sf::Keyboard::Scancode::W){
                    if (camera.y > 0) {
                        camera.y -= 1;
                    }
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    if (camera.y < terrain.getHeight()) {
                        camera.y += 1;
                    }
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    if (camera.x < terrain.getWidth()) {
                        camera.x += 1;
                    }
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    if (camera.x > 0) {
                        camera.x -= 1;
                    }
                }
            }
            else if (const auto* mouse = event->getIf<sf::Event::MouseWheelScrolled>()) {
                float delta = mouse->delta;
                terrain.setTileSize(terrain.getTileSize() + delta);
            }
        }
   
        while (accumulator >= deltaTime) {
			//Update your game logic here, updates vyks reciau negu frames, dabar 20/sec

            accumulator -= deltaTime;
        }

        //Update graphics
        float fps = (currentTime > 0) ? 1.0f / currentTime : 0.0f;
        std::cout << "FPS: " << fps << std::endl;
        
        //Terrain
        terrain.draw(window, camera);


        //Display window
        ImGui::SFML::Render(window);
        window.display();
        window.clear();
    }

    ImGui::SFML::Shutdown();
}

