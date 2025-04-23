#include "Troop.hpp"


#include <memory>
#include <stdexcept>

using namespace TroopEntities;

std::unique_ptr<Troop> TroopCreator::createTroop(TroopType type, const sf::Vector2f& spawnPosition) {
   switch (type) {
   case TroopType::Melee:
       return std::make_unique<Melee>(100, 20, 10, spawnPosition);
   case TroopType::Ranged:
       return std::make_unique<Ranged>(80, 15, 12, 5, spawnPosition);
   case TroopType::Miner:
       return std::make_unique<Miner>(60, 10, 8, 3, spawnPosition);
   case TroopType::Tank:
       return std::make_unique<Tank>(200, 30, 5, 50, spawnPosition);
   default:
       throw std::invalid_argument("Invalid troop type");
   }
}


//spawn Troop
//update troop
//draw troop


