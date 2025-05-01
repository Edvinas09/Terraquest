#include "Wall.h"
#include <SFML/Graphics.hpp>

Wall::Wall(Player* owner, Tile* location, int level)
    : Building(200, 30, 2, "Wall", owner, location), defenseBonus(20), level(level) {
    // Set the color to blue for Wall
    setBuildingColor(sf::Color::Blue);
}

void Wall::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::RectangleShape shape;
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(10, 10));
    shape.setFillColor(getBuildingColor());
    shape.setOrigin(5, 5); // Center the shape for better placement
    window.draw(shape);
}

void Wall::update(int turn) {
    // Implement Wall-specific update logic here, or leave empty if not needed
}

std::string Wall::getDescription() const {
    return "Wall: defensive structure.";
}