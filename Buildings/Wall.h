#ifndef WALL_H
#define WALL_H

#include "Building.h"
#include <SFML/Graphics.hpp>

// Wall class - defensive structure
class Wall : public Building {
private:
    int defenseBonus;
    int level;
    
public:
    Wall(Player* owner, Tile* location, int level = 1);
    
    int getDefenseBonus() const;
    int getLevel() const;
    
    void upgrade();
    void update(int turn) override;
    std::string getDescription() const override;
    void draw(sf::RenderWindow& window, const sf::Vector2f& position) override;
};

#endif
