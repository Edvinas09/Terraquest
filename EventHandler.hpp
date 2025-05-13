#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void run(sf::RenderWindow& window, const std::optional<sf::Event> event); 