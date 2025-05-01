#include "Turret.h"
#include <SFML/Graphics.hpp>

Turret::Turret(Player* owner, Tile* location)
    : Building(150, 100, 10, "Turret", owner, location), attackDamage(50), attackRange(5), attacksPerTurn(2), attacksRemaining(2), automated(true) {}

void Turret::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::CircleShape shape(6);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}

void Turret::update(int turn) {
    // Implement Turret-specific update logic here, or leave empty if not needed
}

std::string Turret::getDescription() const {
    return "Turret: offensive structure.";
} 