#include "Tile.h"

// Constructor implementation
Tile::Tile(int xPos, int yPos, std::string terrain)
    : x(xPos), y(yPos), terrainType(terrain), isOccupied(false) {
}