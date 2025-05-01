#include "Player.h"
#include "Building.h"

Player::Player(const std::string& playerName, int startingResources, sf::Color playerColor)
    : name(playerName), resources(startingResources), color(playerColor) {
}

bool Player::spendResources(int amount) {
    if (resources >= amount) {
        resources -= amount;
        return true;
    }
    return false;
}

void Player::addBuilding(std::unique_ptr<Building> building) {
    buildings.push_back(std::move(building));
}