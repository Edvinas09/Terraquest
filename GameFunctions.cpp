#include "GameFunctions.hpp"

namespace GameFunctions {

    // Define static members of GridHighlight
    bool GridHighlight::highlightGridState = false; 
    int GridHighlight::highlightedTileX = -1;       
    int GridHighlight::highlightedTileY = -1;

    // EntitySpawning implementation
    void EntitySpawning::snapTroopsToGrid(std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize)
    {
        for (auto& troop : troops)
        {
            int gridX = troop->getGridX();
            int gridY = troop->getGridY();

            sf::Vector2f snappedPos(
                gridX * tileSize + tileSize / 2.0f,
                gridY * tileSize + tileSize / 2.0f
            );
            troop->setPosition(snappedPos);
        }
    }

    void EntitySpawning::createTroops(sf::RenderWindow& window, sf::Vector2<float>& camera, TroopEntities::TroopType type,std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        sf::Vector2f worldPos(mousePos.x + camera.x * tileSize, mousePos.y + camera.y * tileSize);
        auto troop = TroopEntities::TroopCreator::createTroop(type, worldPos);
        troops.push_back(std::move(troop));
	}


    void EntitySpawning::spawnTroops(sf::RenderWindow& window, sf::Vector2<float>& camera, std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize)
    {
        for (auto& troop : troops)
        {
            // Calculate world position based on grid coordinates
            sf::Vector2f worldPos(troop.get()->getWorldPosition(tileSize));
            //  pixel-perfect rendering
            sf::Vector2f screenPos = worldPos - sf::Vector2f(camera.x * tileSize, camera.y * tileSize);
            troop->draw(window, screenPos);
        }
    }



    void GridHighlight::calculateHighlightCoordinate(sf::RenderWindow& window,  TerrainNamespace::Terrain& terrain,  sf::Vector2<float>& camera)  
    {  
       sf::Vector2i mousePos = sf::Mouse::getPosition(window);  

       float worldX = mousePos.x + camera.x * terrain.getTileSize();  
       float worldY = mousePos.y + camera.y * terrain.getTileSize();  

       highlightedTileX = static_cast<int>(worldX / terrain.getTileSize());  
       highlightedTileY = static_cast<int>(worldY / terrain.getTileSize());  
    }

    int GridHighlight::getHighlightedTileX()
    {
        return highlightedTileX;
    }

    int GridHighlight::getHighlightedTileY()
    {
        return highlightedTileY;
    }

    bool GridHighlight::changeHighlightGridState()
    {
        highlightGridState = !highlightGridState;
        return highlightGridState;
    }

    bool GridHighlight::getHighlightGridState()
    {
        return highlightGridState;
    }

    bool GridHighlight::setHighlightGridState(bool state)
    {
        highlightGridState = state;
        return highlightGridState;
    }
}
