#ifndef TURRET_H
#define TURRET_H

#include "Building.h"

// Turret class - offensive structure
class Turret : public Building {
private:
    int attackDamage;
    int attackRange;
    int attacksPerTurn;
    int attacksRemaining;
    bool automated;  // If true, attacks automatically nearby enemies
    
public:
    Turret(Player* owner, Tile* location);
    
    int getAttackDamage() const;
    int getAttackRange() const;
    int getAttacksPerTurn() const;
    int getAttacksRemaining() const;
    bool isAutomated() const;
    
    void setAutomated(bool auto_mode);
    void upgrade();
    bool canAttack() const;
    void attack(Building* target);
    
    void update(int turn) override;
    std::string getDescription() const override;
};

#endif // TURRET_H
