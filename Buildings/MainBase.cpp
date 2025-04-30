#include "MainBase.h"
#include <SFML/Graphics.hpp>

MainBase::MainBase(Player* owner, Tile* location)
    : Building(500, 200, 20, "MainBase", owner, location), incomePerTurn(100), unitProductionRate(1), defenseBonus(30) {}

void MainBase::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::RectangleShape shape;
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(14, 14));
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}

void MainBase::update(int turn) {
    // Implement MainBase-specific update logic here, or leave empty if not needed
}

std::string MainBase::getDescription() const {
    return "MainBase: central building for each player.";
} 