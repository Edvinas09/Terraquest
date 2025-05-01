#include "Turret.h"
#include <SFML/Graphics.hpp>

Turret::Turret(Player* owner, Tile* location) {
    : Building(150, 100, 10, "Turret", owner, location), attackDamage(50), attackRange(5), attacksPerTurn(2), attacksRemaining(2), automated(true) {}
    // Set the color to red for Turret
    setBuildingColor(sf::Color::Blue);
}

void Turret::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::RectangleShape shape;
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(14, 14));
    shape.setFillColor(getBuildingColor());
	shape.setOrigin(7, 7); // Center the shape for better placement
    window.draw(shape);
}

void Turret::update(int turn) {
    // Implement Turret-specific update logic here, or leave empty if not needed
}

std::string Turret::getDescription() const {
    return "Turret: offensive structure.";
} 