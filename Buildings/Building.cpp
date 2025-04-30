#include "Building.h"
#include <SFML/Graphics.hpp>

// Constructor implementation
Building::Building(int hp, int bCost, int mCost, std::string buildingName, Player* buildingOwner, Tile* buildingLocation)
    : healthPoints(hp), buildCost(bCost), maintenanceCost(mCost), name(buildingName), owner(buildingOwner), location(buildingLocation), isDestroyed(false) {}

// Destructor implementation
Building::~Building() = default;

// Getters
int Building::getHealth() const { return healthPoints; }
int Building::getBuildCost() const { return buildCost; }
int Building::getMaintenanceCost() const { return maintenanceCost; }
std::string Building::getName() const { return name; }
Player* Building::getOwner() const { return owner; }
Tile* Building::getLocation() const { return location; }
bool Building::getIsDestroyed() const { return isDestroyed; }

// Common methods
void Building::takeDamage(int damage) {
    healthPoints -= damage;
    if (healthPoints <= 0) isDestroyed = true;
}

void Building::repair(int amount) {
    healthPoints += amount;
    // Optionally clamp to a max value if you have one
}

std::string Building::getDescription() const {
    return name;
}

void Building::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::RectangleShape shape;
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(10, 10));
    shape.setFillColor(sf::Color(128, 128, 128)); // Default gray
    window.draw(shape);
} 
