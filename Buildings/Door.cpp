#include "Door.h"
#include <SFML/Graphics.hpp>

Door::Door(Player* owner, Tile* location)
    : Building(100, 50, 5, "Door", owner, location), isOpen(false), closedDefenseBonus(10) {}

void Door::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::RectangleShape shape;
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(10, 10));
    shape.setFillColor(sf::Color(139, 69, 19)); // Brown
    window.draw(shape);
}

void Door::update(int turn) {
    // Implement Door-specific update logic here, or leave empty if not needed
}

std::string Door::getDescription() const {
    return "Door: allows passage through walls.";
} 