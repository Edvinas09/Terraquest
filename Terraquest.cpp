#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "First window");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;

    auto const deltaTime = 1.0f / 20;
	float accumulator = 0.0f;

    while (window.isOpen()) {
		// Process events
		auto currentTime = deltaClock.restart().asSeconds();
        accumulator += currentTime;

        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
   
        while (accumulator >= deltaTime) {
			// Update your game logic here







            accumulator -= deltaTime;
        }
        float fps = (currentTime > 0) ? 1.0f / currentTime : 0.0f;
        std::cout << "FPS: " << fps << std::endl;
        ImGui::SFML::Update(window, deltaClock.restart());


        ImGui::Begin("Hello, world!");
        ImGui::Button("Button");
        ImGui::End();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
        
    }

    ImGui::SFML::Shutdown();
}

