#include "MainBase.h"

MainBase::MainBase(Player* owner, Tile* location)
    : Building(100, 0, 5, "Main Base", owner, location),
      incomePerTurn(10), unitProductionRate(1), defenseBonus(5) {
    availableUnits = {"Peasant", "Spearman"};  // Basic units available at start
}

int MainBase::getIncomePerTurn() const { 
    return incomePerTurn; 
}

int MainBase::getDefenseBonus() const { 
    return defenseBonus; 
}

void MainBase::upgradeBase() {
    incomePerTurn += 5;
    unitProductionRate += 1;
    defenseBonus += 2;
    
    // Unlock more advanced units as the base gets upgraded
    if (unitProductionRate == 2) {
        availableUnits.push_back("Archer");
    } else if (unitProductionRate == 3) {
        availableUnits.push_back("Knight");
    }
}

const std::vector<std::string>& MainBase::getAvailableUnits() const {
    return availableUnits;
}

void MainBase::update(int turn) {
    // Generate income for the owner each turn
    // This would interact with the Player class to add money
}

std::string MainBase::getDescription() const {
    return Building::getDescription() + " - Income: " + std::to_string(incomePerTurn) + 
           ", Defense Bonus: " + std::to_string(defenseBonus);
}
