#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.h"

// Forward declarations
class Player;

// Base Building class that all specific buildings will inherit from
class Building {
protected:
    int healthPoints;
    int buildCost;
    int maintenanceCost;
    std::string name;
    Player* owner;
    Tile* location;
    bool isDestroyed;
    sf::Color buildingColor;

public:
    Building(int hp, int bCost, int mCost, std::string buildingName, Player* buildingOwner, Tile* buildingLocation);
    virtual ~Building();

    // Getters
    int getHealth() const;
    int getBuildCost() const;
    int getMaintenanceCost() const;
    std::string getName() const;
    Player* getOwner() const;
    Tile* getLocation() const;
    bool getIsDestroyed() const;
    sf::Color getBuildingColor() const;

    // Setters
    void setLocation(Tile* newLocation);
    void setBuildingColor(sf::Color color);

    // Common methods
    virtual void takeDamage(int damage);
    virtual void repair(int amount);
    virtual void update(int turn) = 0;  // Abstract method to be implemented by derived classes
    virtual std::string getDescription() const;
    virtual void draw(sf::RenderWindow& window, const sf::Vector2f& position);
};

#endif