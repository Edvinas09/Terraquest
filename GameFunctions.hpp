#pragma once
#include <vector>

#include "Terrain/Terrain.h"
#include "Troop/Troop.hpp"
#include "Buildings/Building.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GameFunctions {

	class EntitySpawning
	{
	public:
		static void snapTroopsToGrid(std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize);
		static void spawnTroops(sf::RenderWindow& window, sf::Vector2<float>& camera, std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, TerrainNamespace::Terrain& terrain);
		static void createTroops(sf::RenderWindow& window, sf::Vector2<float>& camera, TroopEntities::TroopType type, std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize);

		// Building spawning functions
		static void snapBuildingsToGrid(std::vector<std::unique_ptr<BuildingEntities::Building>>& buildings, float tileSize);
		static void spawnBuildings(sf::RenderWindow& window, sf::Vector2<float>& camera, std::vector<std::unique_ptr<BuildingEntities::Building>>& buildings, float tileSize);
		static void createBuildings(sf::RenderWindow& window, sf::Vector2<float>& camera, BuildingEntities::BuildingType type, std::vector<std::unique_ptr<BuildingEntities::Building>>& buildings, float tileSize);
	};

	class GridHighlight
	{
	private:
		static bool highlightGridState;
		static int highlightedTileX;
		static int highlightedTileY;

	public:
		static void calculateHighlightCoordinate(sf::RenderWindow& window, TerrainNamespace::Terrain& terrain, sf::Vector2<float>& camera);

		static int getHighlightedTileX();
		static int getHighlightedTileY();
		static bool changeHighlightGridState();
		static bool getHighlightGridState();
		static bool setHighlightGridState(bool state);
	};

	namespace PathFinding {
		std::vector<sf::Vector2i> FindPath(
			int startX, int startY, int endX, int endY,
			const std::vector<std::vector<bool>>& obstacleGrid
		);
	}
}
