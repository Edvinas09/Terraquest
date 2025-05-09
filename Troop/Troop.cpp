#include "Troop.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <stdexcept>

#include <memory>
#include <stdexcept>

using namespace TroopEntities;

std::unique_ptr<Troop> TroopCreator::createTroop(TroopType type, const sf::Vector2f& spawnPosition) {
   switch (type) {
   case TroopType::Melee:
       return std::make_unique<Melee>(100, 20, 10, spawnPosition);
   case TroopType::Ranged:
       return std::make_unique<Ranged>(80, 15, 12, 5, spawnPosition);
   case TroopType::Miner:
       return std::make_unique<Miner>(60, 10, 8, 3, spawnPosition);
   case TroopType::Tank:
       return std::make_unique<Tank>(200, 30, 5, 50, spawnPosition);
   default:
       throw std::invalid_argument("Invalid troop type");
   }
}

void Troop::draw(sf::RenderWindow& window, const sf::Vector2f& position)
{
	sf::RectangleShape shape;
	shape.setPosition(position);
	shape.setSize(sf::Vector2f(5, 5));
	shape.setFillColor(sf::Color::Red);
	window.draw(shape);
}
