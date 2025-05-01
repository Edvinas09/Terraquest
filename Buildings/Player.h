#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

// Forward declarations
class Building;

class Player {
private:
    std::string name;
    int resources;
    sf::Color color;
    std::vector<std::unique_ptr<Building>> buildings;

public:
    Player(const std::string& playerName, int startingResources, sf::Color playerColor);

    // Getters
    std::string getName() const { return name; }
    int getResources() const { return resources; }
    sf::Color getColor() const { return color; }

    // Resource management
    void addResources(int amount) { resources += amount; }
    bool spendResources(int amount);

    // Building management
    void addBuilding(std::unique_ptr<Building> building);
    const std::vector<std::unique_ptr<Building>>& getBuildings() const { return buildings; }
};

#endif // PLAYER_H