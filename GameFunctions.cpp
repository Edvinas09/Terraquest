#include "GameFunctions.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include <vector>
#include <queue>
#include <set>
#include <map>

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
			troop->draw(window, sf::Vector2f(worldPos.x - camera.x * terrain.getTileSize(), worldPos.y - camera.y * terrain.getTileSize()), terrain.getTileSize());
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
	namespace PathFinding {

		std::vector<sf::Vector2i> FindPath(
			int startX, int startY, int endX, int endY,
			const std::vector<std::vector<bool>>& obstacleGrid)
		{
			struct Node {
				int x, y;
				float g, h;
				Node* parent;
				Node(int x, int y, float g, float h, Node* parent = nullptr)
					: x(x), y(y), g(g), h(h), parent(parent) {
				}
				float f() const { return g + h; }
			};

			auto heuristic = [&](int x, int y) {
				return std::abs(x - endX) + std::abs(y - endY);
				};

			auto cmp = [](const Node* a, const Node* b) { return a->f() > b->f(); };
			std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> open(cmp);
			std::set<std::pair<int, int>> closed;
			std::map<std::pair<int, int>, Node*> allNodes;

			Node* start = new Node(startX, startY, 0, heuristic(startX, startY));
			open.push(start);
			allNodes[{startX, startY}] = start;

			std::vector<std::pair<int, int>> directions = {
				{1,0},{-1,0},{0,1},{0,-1}
			};

			while (!open.empty()) {
				Node* current = open.top(); open.pop();
				if (current->x == endX && current->y == endY) {
					std::vector<sf::Vector2i> path;
					Node* n = current;
					while (n) {
						path.push_back({ n->x, n->y });
						n = n->parent;
					}
					std::reverse(path.begin(), path.end());
					for (auto& kv : allNodes) delete kv.second;
					return path;
				}
				closed.insert({ current->x, current->y });
				for (auto& d : directions) {
					int nx = current->x + d.first, ny = current->y + d.second;
					if (nx < 0 || ny < 0 || nx >= (int)obstacleGrid.size() || ny >= (int)obstacleGrid[0].size())
						continue;
					if (obstacleGrid[nx][ny]) continue;
					if (closed.count({ nx, ny })) continue;
					float g = current->g + 1;
					float h = heuristic(nx, ny);
					Node* neighbor = new Node(nx, ny, g, h, current);
					if (allNodes.count({ nx, ny }) == 0 || neighbor->f() < allNodes[{nx, ny}]->f()) {
						open.push(neighbor);
						allNodes[{nx, ny}] = neighbor;
					}
					else {
						delete neighbor;
					}
				}
			}
			for (auto& kv : allNodes) delete kv.second;
			return {};
		}

	}
} 