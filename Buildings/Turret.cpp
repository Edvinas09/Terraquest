#include "Turret.h"

Turret::Turret(Player* owner, Tile* location)
    : Building(40, 20, 3, "Turret", owner, location),
      attackDamage(10), attackRange(2), attacksPerTurn(1), attacksRemaining(1), automated(false) {}

int Turret::getAttackDamage() const { 
    return attackDamage; 
}

int Turret::getAttackRange() const { 
    return attackRange; 
}

int Turret::getAttacksPerTurn() const { 
    return attacksPerTurn; 
}

int Turret::getAttacksRemaining() const { 
    return attacksRemaining; 
}

bool Turret::isAutomated() const { 
    return automated; 
}

void Turret::setAutomated(bool auto_mode) {
    automated = auto_mode;
}

void Turret::upgrade() {
    attackDamage += 5;
    healthPoints += 10;
    maintenanceCost += 1;
}

bool Turret::canAttack() const {
    return attacksRemaining > 0 && !isDestroyed;
}

void Turret::attack(Building* target) {
    if (canAttack()) {
        target->takeDamage(attackDamage);
        attacksRemaining--;
    }
}

void Turret::update(int turn) {
    // Reset attacks at the beginning of player's turn
    attacksRemaining = attacksPerTurn;
    
    // If automated, the game logic would handle automatic attacks here
}

std::string Turret::getDescription() const {
    return Building::getDescription() + " - Damage: " + std::to_string(attackDamage) + 
           ", Range: " + std::to_string(attackRange) + 
           ", Attacks: " + std::to_string(attacksRemaining) + "/" + std::to_string(attacksPerTurn);
}
