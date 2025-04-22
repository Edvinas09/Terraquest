#ifndef DOOR_H
#define DOOR_H

#include "Building.h"

// Door class - allows passage through walls
class Door : public Building {
private:
    bool isOpen;
    int closedDefenseBonus;
    
public:
    Door(Player* owner, Tile* location);
    
    bool getIsOpen() const;
    int getClosedDefenseBonus() const;
    
    void toggleDoor();
    int getCurrentDefenseBonus() const;
    
    void update(int turn) override;
    std::string getDescription() const override;
};

#endif
