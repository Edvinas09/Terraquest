#include "Building.h"

Building::Building(int hp, int bCost, int mCost, std::string buildingName, Player* buildingOwner, Tile* buildingLocation)
    : healthPoints(hp), buildCost(bCost), maintenanceCost(mCost), 
      name(buildingName), owner(buildingOwner), location(buildingLocation), isDestroyed(false) {}

Building::~Building() {}

int Building::getHealth() const { 
    return healthPoints; 
}

int Building::getBuildCost() const { 
    return buildCost; 
}

int Building::getMaintenanceCost() const { 
    return maintenanceCost; 
}

std::string Building::getName() const { 
    return name; 
}

Player* Building::getOwner() const { 
    return owner; 
}

Tile* Building::getLocation() const { 
    return location; 
}

bool Building::getIsDestroyed() const { 
    return isDestroyed; 
}

void Building::takeDamage(int damage) {
    healthPoints -= damage;
    if (healthPoints <= 0) {
        isDestroyed = true;
        healthPoints = 0;
    }
}

void Building::repair(int amount) {
    if (!isDestroyed) {
        healthPoints += amount;
    }
}

std::string Building::getDescription() const {
    return name + " (HP: " + std::to_string(healthPoints) + ")";
}
