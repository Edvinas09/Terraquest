#ifndef TILE_H
#define TILE_H

#include <string>
#include <SFML/Graphics.hpp>

// Forward declarations
class Building;

// Tile class representing a single grid cell in the game world
class Tile {
private:
    int x, y;                // Coordinates in the grid
    std::string terrainType; // Type of terrain (grass, water, etc.)
    bool isOccupied;         // Whether the tile has a building or unit

public:
    Tile(int xPos, int yPos, std::string terrain = "grass");

    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    std::string getTerrainType() const { return terrainType; }
    bool getIsOccupied() const { return isOccupied; }

    // Setters
    void setTerrainType(const std::string& terrain) { terrainType = terrain; }
    void setIsOccupied(bool occupied) { isOccupied = occupied; }

    // Calculate world position based on grid position and tile size
    sf::Vector2f getWorldPosition(float tileSize) const {
        return sf::Vector2f(
            x * tileSize + tileSize / 2.0f,
            y * tileSize + tileSize / 2.0f
        );
    }
};

#endif // TILE_H