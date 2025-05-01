#include "BuildingFactory.h"
#include "MainBase.h"
#include "Wall.h"
#include "Door.h"
#include "Turret.h"

std::unique_ptr<Building> BuildingFactory::createBuilding(std::string type, Player* owner, Tile* location) {
    if (type == "MainBase") {
        return std::make_unique<MainBase>(owner, location);
    } else if (type == "Wall") {
        return std::make_unique<Wall>(owner, location);
    } else if (type == "Door") {
        return std::make_unique<Door>(owner, location);
    } else if (type == "Turret") {
        return std::make_unique<Turret>(owner, location);
    }
    
    return nullptr;  // Unknown building type
}
