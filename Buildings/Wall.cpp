#include "Wall.h"

Wall::Wall(Player* owner, Tile* location, int level)
    : Building(30 * level, 10 * level, 1, "Wall", owner, location),
      defenseBonus(5 * level), level(level) {}

int Wall::getDefenseBonus() const { 
    return defenseBonus; 
}

int Wall::getLevel() const { 
    return level; 
}

void Wall::upgrade() {
    level++;
    defenseBonus = 5 * level;
    healthPoints = 30 * level;
    maintenanceCost = level;
}

void Wall::update(int turn) {
    // Walls could slowly regenerate health over time
    if (healthPoints < 30 * level && !isDestroyed) {
        repair(1);
    }
}

std::string Wall::getDescription() const {
    return Building::getDescription() + " - Level " + std::to_string(level) + 
           ", Defense Bonus: " + std::to_string(defenseBonus);
}
