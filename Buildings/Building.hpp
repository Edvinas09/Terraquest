#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>

namespace BuildingEntities {

    enum class BuildingType {
        MainBase,
        Tower,
        Wall,
        Door
    };

    class Building {
    private:
        int health;
        int gridX, gridY;
        sf::Vector2f position;

    public:
        Building(int health, const sf::Vector2f& position)
            : health(health), position(position), gridX(-1), gridY(-1) {
        }
        virtual ~Building() = default;

        int getHealth() const { return health; }
        sf::Vector2f getPosition() const { return position; }
        int getGridX() const { return gridX; }
        int getGridY() const { return gridY; }

        sf::Vector2f getWorldPosition(float tileSize) const {
            if (gridX == -1 || gridY == -1) {
                return position;
            }
            return sf::Vector2f(
                gridX * tileSize + tileSize / 2.0f,
                gridY * tileSize + tileSize / 2.0f
            );
        }

        void setGridCoordinates(int x, int y) {
            gridX = x;
            gridY = y;
            // Update position based on grid coordinates
            position = sf::Vector2f(x, y);
        }
        void setHealth(int newHealth) { health = newHealth; }
        void setPosition(const sf::Vector2f& newPosition) { 
            position = newPosition;
            // Reset grid coordinates when position is set directly
            gridX = -1;
            gridY = -1;
        }

        void draw(sf::RenderWindow& window, const sf::Vector2f& position);

        virtual std::string toString() const {
            std::ostringstream oss;
            oss << "Building: Health=" << health
                << ", Position=(" << position.x << ", " << position.y << ")"
                << ", Grid=(" << gridX << ", " << gridY << ")";
            return oss.str();
        }
    };

    class BuildingCreator {
    public:
        static std::unique_ptr<Building> createBuilding(BuildingType type, const sf::Vector2f& spawnPosition);
    };

    class MainBase : public Building { 
    public:
        MainBase(int health, const sf::Vector2f& position)
            : Building(health, position) {}
    };

    class Tower : public Building {
        int range;
    public:
        Tower(int health, int range, const sf::Vector2f& position)
            : Building(health, position), range(range) {}
        
        int getRange() const { return range; }
        void setRange(int newRange) { range = newRange; }

        std::string toString() const override {
            std::ostringstream oss;
            oss << Building::toString() << ", Range=" << range;
            return oss.str();
        }
    };

    class Wall : public Building { 
    public:
        Wall(int health, const sf::Vector2f& position)
            : Building(health, position) {}
    };

    class Door : public Building { 
    public:
        Door(int health, const sf::Vector2f& position)
            : Building(health, position) {}
    };
} 