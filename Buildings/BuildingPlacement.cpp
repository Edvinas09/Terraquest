#include "BuildingPlacement.h"
#include "BuildingFactory.h"
#include "MainBase.h"
#include "Wall.h"
#include "Door.h"
#include "Turret.h"
#include <SFML/Graphics.hpp>

namespace BuildingSystem {

    // Initialize static members
    BuildingType BuildingPlacement::selectedBuildingType = BuildingType::Wall;
    bool BuildingPlacement::isPlacingBuilding = false;

    // Initialize building selection buttons
    void BuildingPlacement::initButtons(std::vector<std::unique_ptr<UI::Button>>& buttons, const sf::Font& font) {
        // Create buttons for each building type
        auto wallButton = std::make_unique<UI::Button>(
            sf::Vector2f(100, 40), "Wall", sf::Color::Blue, sf::Color::White, font
        );
        wallButton->setPosition(sf::Vector2f(50, 50));

        auto doorButton = std::make_unique<UI::Button>(
            sf::Vector2f(100, 40), "Door", sf::Color(139, 69, 19), sf::Color::White, font
        );
        doorButton->setPosition(sf::Vector2f(50, 100));

        auto turretButton = std::make_unique<UI::Button>(
            sf::Vector2f(100, 40), "Turret", sf::Color::Red, sf::Color::White, font
        );
        turretButton->setPosition(sf::Vector2f(50, 150));

        auto baseButton = std::make_unique<UI::Button>(
            sf::Vector2f(100, 40), "Base", sf::Color::Green, sf::Color::White, font
        );
        baseButton->setPosition(sf::Vector2f(50, 200));

        // Add buttons to vector
        buttons.push_back(std::move(wallButton));
        buttons.push_back(std::move(doorButton));
        buttons.push_back(std::move(turretButton));
        buttons.push_back(std::move(baseButton));
    }

    // Create building based on type
    std::unique_ptr<Building> BuildingPlacement::createBuilding(BuildingType type, Player* owner, Tile* location) {
        std::string buildingType;

        switch (type) {
        case BuildingType::MainBase:
            buildingType = "MainBase";
            break;
        case BuildingType::Wall:
            buildingType = "Wall";
            break;
        case BuildingType::Door:
            buildingType = "Door";
            break;
        case BuildingType::Turret:
            buildingType = "Turret";
            break;
        default:
            buildingType = "Wall"; // Default to Wall
        }

        return BuildingFactory::createBuilding(buildingType, owner, location);
    }

    // Place building at the given location
    void BuildingPlacement::placeBuilding(
        std::vector<std::unique_ptr<Building>>& buildings,
        Player* owner,
        Tile* location,
        BuildingType type
    ) {
        auto building = createBuilding(type, owner, location);
        buildings.push_back(std::move(building));
    }

    // Draw all buildings on screen
    void BuildingPlacement::drawBuildings(
        sf::RenderWindow& window,
        const sf::Vector2<float>& camera,
        std::vector<std::unique_ptr<Building>>& buildings,
        float tileSize
    ) {
        for (auto& building : buildings) {
            // Get building location and calculate screen position
            Tile* location = building->getLocation();
            int gridX = location->getX();
            int gridY = location->getY();

            sf::Vector2f worldPos(
                gridX * tileSize + tileSize / 2.0f,
                gridY * tileSize + tileSize / 2.0f
            );

            // Convert world position to screen position
            sf::Vector2f screenPos = worldPos - sf::Vector2f(camera.x * tileSize, camera.y * tileSize);

            // Draw the building
            building->draw(window, screenPos);
        }
    }

    // Getters and setters
    BuildingType BuildingPlacement::getSelectedBuildingType() {
        return selectedBuildingType;
    }

    void BuildingPlacement::setSelectedBuildingType(BuildingType type) {
        selectedBuildingType = type;
    }

    bool BuildingPlacement::getIsPlacingBuilding() {
        return isPlacingBuilding;
    }

    void BuildingPlacement::setIsPlacingBuilding(bool isPlacing) {
        isPlacingBuilding = isPlacing;
    }

    void BuildingPlacement::togglePlacingBuilding() {
        isPlacingBuilding = !isPlacingBuilding;
    }

} // namespace BuildingSystem