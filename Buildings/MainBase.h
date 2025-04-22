#ifndef MAINBASE_H
#define MAINBASE_H

#include "Building.h"
#include <vector>
#include <string>

// MainBase class - central building for each player
class MainBase : public Building {
private:
    int incomePerTurn;
    int unitProductionRate;
    std::vector<std::string> availableUnits;
    int defenseBonus;

public:
    MainBase(Player* owner, Tile* location);
    
    int getIncomePerTurn() const;
    int getDefenseBonus() const;
    
    void upgradeBase();
    const std::vector<std::string>& getAvailableUnits() const;
    
    void update(int turn) override;
    std::string getDescription() const override;
};

#endif // MAINBASE_H
