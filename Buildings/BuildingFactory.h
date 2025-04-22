#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

#include <memory>
#include <string>
#include "Building.h"

class Player;
class Tile;

// Factory class to create buildings
class BuildingFactory {
public:
    static std::unique_ptr<Building> createBuilding(std::string type, Player* owner, Tile* location);
};

#endif // BUILDINGFACTORY_H
