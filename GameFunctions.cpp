#include "GameFunctions.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

namespace GameFunctions {

	// Define static members of GridHighlight
	bool GridHighlight::highlightGridState = false;
	int GridHighlight::highlightedTileX = 0;
	int GridHighlight::highlightedTileY = 0;

	// EntitySpawning implementation
	void EntitySpawning::snapTroopsToGrid(std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize)
	{
		for (auto& troop : troops)
		{
			sf::Vector2f worldPos = troop->getWorldPosition(tileSize);
			troop->setPosition(worldPos);
		}
	}

	void EntitySpawning::createTroops(sf::RenderWindow& window, sf::Vector2<float>& camera, TroopEntities::TroopType type, std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, float tileSize)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		sf::Vector2f worldPos = sf::Vector2f(mousePos.x + camera.x, mousePos.y + camera.y);
		troops.push_back(TroopEntities::TroopCreator::createTroop(type, worldPos));
	}


	void EntitySpawning::spawnTroops(sf::RenderWindow& window, sf::Vector2<float>& camera, std::vector<std::unique_ptr<TroopEntities::Troop>>& troops, TerrainNamespace::Terrain& terrain)
	{
;
		for (auto& troop : troops)
		{
			sf::Vector2f worldPos = troop->getWorldPosition(terrain.getTileSize());
			troop->draw(window, sf::Vector2f(worldPos.x - camera.x * terrain.getTileSize(),worldPos.y - camera.y * terrain.getTileSize()));
		}
	}

	// Building spawning functions
	void EntitySpawning::snapBuildingsToGrid(std::vector<std::unique_ptr<BuildingEntities::Building>>& buildings, float tileSize) {
		for (auto& building : buildings) {
			sf::Vector2f worldPos = building->getWorldPosition(tileSize);
			building->setPosition(worldPos);
		}
	}

	void EntitySpawning::spawnBuildings(sf::RenderWindow& window, sf::Vector2<float>& camera, std::vector<std::unique_ptr<BuildingEntities::Building>>& buildings, float tileSize) {
		for (auto& building : buildings) {
			sf::Vector2f worldPos = building->getWorldPosition(tileSize);
			building->draw(window, sf::Vector2f(worldPos.x - camera.x * tileSize, worldPos.y - camera.y * tileSize));
		}
	}

	void EntitySpawning::createBuildings(sf::RenderWindow& window, sf::Vector2<float>& camera, BuildingEntities::BuildingType type, std::vector<std::unique_ptr<BuildingEntities::Building>>& buildings, float tileSize) {
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		sf::Vector2f worldPos = sf::Vector2f(mousePos.x + camera.x, mousePos.y + camera.y);
		buildings.push_back(BuildingEntities::BuildingCreator::createBuilding(type, worldPos));
	}

	void GridHighlight::calculateHighlightCoordinate(sf::RenderWindow& window, TerrainNamespace::Terrain& terrain, sf::Vector2<float>& camera)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

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
