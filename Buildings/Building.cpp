#include "Building.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <stdexcept>
#include <memory>

using namespace BuildingEntities;

std::unique_ptr<Building> BuildingCreator::createBuilding(BuildingType type, const sf::Vector2f& spawnPosition) {
    switch (type) {
    case BuildingType::MainBase:
        return std::make_unique<MainBase>(1000, spawnPosition);
    case BuildingType::Tower:
        return std::make_unique<Tower>(500, 10, spawnPosition);
    case BuildingType::Wall:
        return std::make_unique<Wall>(300, spawnPosition);
    case BuildingType::Door:
        return std::make_unique<Door>(200, spawnPosition);
    default:
        throw std::invalid_argument("Invalid building type");
    }
}

void Building::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::RectangleShape shape;
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(10, 10));
    
    // Different colors for different building types
    if (dynamic_cast<MainBase*>(this)) {
        shape.setFillColor(sf::Color::Blue);
    }
    else if (dynamic_cast<Tower*>(this)) {
        shape.setFillColor(sf::Color::Yellow);
    }
    else if (dynamic_cast<Wall*>(this)) {
        shape.setFillColor(sf::Color::Green);
    }
    else if (dynamic_cast<Door*>(this)) {
        shape.setFillColor(sf::Color::Magenta);
    }
    
    window.draw(shape);
} 