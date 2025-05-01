#pragma once
#include <vector>

#include "Terrain/Terrain.h"
#include "Troop/Troop.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GameFunctions {

    class EntitySpawning
    {
    public:
         static void snapTroopsToGrid(std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize);
         static void spawnTroops(sf::RenderWindow& window, sf::Vector2<float>& camera,std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize);
         static void createTroops(sf::RenderWindow& window, sf::Vector2<float>& camera, std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize);    };

    class GridHighlight
    {
    private:
         static bool highlightGridState;
         static int highlightedTileX;
         static int highlightedTileY;

    public:
         static void calculateHighlightCoordinate(sf::RenderWindow& window,TerrainNamespace::Terrain& terrain, sf::Vector2<float>& camera);

         static int getHighlightedTileX();
         static int getHighlightedTileY();
         static bool changeHighlightGridState();
         static bool getHighlightGridState();
         static bool setHighlightGridState(bool state);
    };
}
