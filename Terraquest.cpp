#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Terrain/Terrain.h"
#include "UI.hpp"
#include "Troop/Troop.hpp"
#include "Buildings/Building.hpp"
#include "GameFunctions.hpp"
#include "EventHandler.hpp"

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



	//Main game loop
	while (window.isOpen()) {
		//Clocks
		auto currentTime = deltaClock.restart().asSeconds();
		accumulator += currentTime;



		//Event proceesing
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);


			run(window, event);

		
		// Update ImGui
		ImGui::SFML::Update(window, sf::seconds(currentTime));

		while (accumulator >= deltaTime) {
			//Update your game logic here, updates vyks reciau negu frames, dabar 20/sec
			accumulator -= deltaTime;
		}

		//Update graphics
		float fps = (currentTime > 0) ? 1.0f / currentTime : 0.0f;
		//std::cout << "FPS: " << fps << std::endl;

		window.clear();

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}