
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Terrain/Terrain.h"
#include "UI.hpp"
#include "Troop/Troop.hpp"
#include "Buildings/Building.hpp"
#include "GameFunctions.hpp"


void draw(sf::RenderWindow& window, TerrainNamespace::Terrain terrain, ) {

	//Terrain
	terrain.draw(window, camera,
		GameFunctions::GridHighlight::getHighlightGridState() ? GameFunctions::GridHighlight::getHighlightedTileX() : -1,
		GameFunctions::GridHighlight::getHighlightGridState() ? GameFunctions::GridHighlight::getHighlightedTileY() : -1);


	GameFunctions::EntitySpawning::spawnTroops(window, camera, troops, terrain.getTileSize());
	GameFunctions::EntitySpawning::spawnBuildings(window, camera, buildings, terrain.getTileSize());

}
