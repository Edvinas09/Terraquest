#include "BuildingFactory.h"
#include "MainBase.h"
#include "Wall.h"
#include "Door.h"
#include "Turret.h"

std::unique_ptr<Building> BuildingFactory::createBuilding(std::string type, Player* owner, Tile* location) {
    std::unique_ptr<Building> building = nullptr;

    if (type == "MainBase") {
        building = std::make_unique<MainBase>(owner, location);
    }
    else if (type == "Wall") {
        building = std::make_unique<Wall>(owner, location);
    }
    else if (type == "Door") {
        building = std::make_unique<Door>(owner, location);
    }
    else if (type == "Turret") {
        building = std::make_unique<Turret>(owner, location);
    }

    // Mark the tile as occupied if a building was created
    if (building && location) {
        location->setIsOccupied(true);
    }

    return building;
}