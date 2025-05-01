#ifndef BUILDINGPLACEMENT_H
#define BUILDINGPLACEMENT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Building.h"
#include "../UI.hpp"

class Tile;
class Player;

namespace BuildingSystem {

    enum class BuildingType {
        MainBase,
        Wall,
        Door,
        Turret
    };

    class BuildingPlacement {
    private:
        static BuildingType selectedBuildingType;
        static bool isPlacingBuilding;

    public:
        // Initialize building placement UI buttons
        static void initButtons(std::vector<std::unique_ptr<UI::Button>>& buttons, const sf::Font& font);

        // Create building at the given position with the selected type
        static std::unique_ptr<Building> createBuilding(BuildingType type, Player* owner, Tile* location);

        // Place buildings on the map
        static void placeBuilding(
            std::vector<std::unique_ptr<Building>>& buildings,
            Player* owner,
            Tile* location,
            BuildingType type
        );

        // Draw all buildings on screen
        static void drawBuildings(
            sf::RenderWindow& window,
            const sf::Vector2<float>& camera,
            std::vector<std::unique_ptr<Building>>& buildings,
            float tileSize
        );

        // Getters and setters
        static BuildingType getSelectedBuildingType();
        static void setSelectedBuildingType(BuildingType type);
        static bool getIsPlacingBuilding();
        static void setIsPlacingBuilding(bool isPlacing);
        static void togglePlacingBuilding();
    };

} // namespace BuildingSystem

#endif // BUILDINGPLACEMENT_H