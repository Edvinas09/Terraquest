#include "Door.h"

Door::Door(Player* owner, Tile* location)
    : Building(25, 15, 2, "Door", owner, location),
      isOpen(false), closedDefenseBonus(3) {}

bool Door::getIsOpen() const { 
    return isOpen; 
}

int Door::getClosedDefenseBonus() const { 
    return closedDefenseBonus; 
}

void Door::toggleDoor() {
    isOpen = !isOpen;
}

int Door::getCurrentDefenseBonus() const {
    return isOpen ? 0 : closedDefenseBonus;
}

void Door::update(int turn) {
    // Doors might automatically close at night or under attack
    // This would depend on game mechanics
}

std::string Door::getDescription() const {
    std::string status = isOpen ? "Open" : "Closed";
    return Building::getDescription() + " - Status: " + status;
}
