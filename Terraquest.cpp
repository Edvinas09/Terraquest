#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Terrain/Terrain.h"
#include "UI.hpp"
#include "Troop/Troop.hpp"
#include "Buildings/Building.hpp"
#include "GameFunctions.hpp"

#include <iostream>

enum class PlacementMode {
	None,
	Troop,
	Building
};

int main() {
	//Init window
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Terraquest");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	//Clock for fps and physics
	sf::Clock deltaClock;
	auto const deltaTime = 1.0f / 20;
	float accumulator = 0.0f;
	ImGui::SFML::Update(window, deltaClock.restart());

	//Placement tracking
	PlacementMode currentPlacementMode = PlacementMode::None;
	BuildingEntities::BuildingType currentBuildingType = BuildingEntities::BuildingType::MainBase;
	TroopEntities::TroopType currentTroopType = TroopEntities::TroopType::Melee;
	bool isObstacle = false;

	//Font for the game
	sf::Font font;
	font.openFromFile("resources/fonts/arial.ttf");

	//Camera
	sf::Vector2<float> camera = { 0, 0 };
	bool up = false, down = false, left = false, right = false;
	float xMovement = 0.0, yMovement = 0.0;

	//Terrain
	TerrainNamespace::Terrain terrain(200, 200, 2);
	sf::Color color;
	int resourceType;

	//Troops
	std::vector<std::unique_ptr<TroopEntities::Troop>> troops;
	sf::Vector2f troopPosition;
	int selectedTroopIndex = -1;

	//Resources;
	int resource;

	//Buildings
	std::vector<std::unique_ptr<BuildingEntities::Building>> buildings;

	//Obtable vector
	std::vector<sf::Vector2<int>> oldLocations;

	//Troop Buttons
	UI::Button melee_button({ 200, 50 }, "Melee", sf::Color::Red, sf::Color::White, font);
	melee_button.setPosition({ 1000, 700 });
	melee_button.setFont(font);
	melee_button.setTextColor(sf::Color::White);

	UI::Button tank_button({ 200, 50 }, "Tank", sf::Color::Red, sf::Color::White, font);
	tank_button.setPosition({ 750,700 });
	tank_button.setFont(font);
	tank_button.setTextColor(sf::Color::White);

	UI::Button archer_button({ 200, 50 }, "Archer", sf::Color::Red, sf::Color::White, font);
	archer_button.setPosition({ 500, 700 });
	archer_button.setFont(font);
	archer_button.setTextColor(sf::Color::White);

	UI::Button miner_button({ 200, 50 }, "Miner", sf::Color::Red, sf::Color::White, font);
	miner_button.setPosition({ 200,700 });
	miner_button.setFont(font);
	miner_button.setTextColor(sf::Color::White);


	//Building Buttons
	UI::Button mainbase_button({ 200, 50 }, "Main Base", sf::Color::Blue, sf::Color::White, font);
	mainbase_button.setPosition({ 1000, 600 });
	mainbase_button.setFont(font);
	mainbase_button.setTextColor(sf::Color::White);

	UI::Button tower_button({ 200, 50 }, "Tower", sf::Color::Yellow, sf::Color::White, font);
	tower_button.setPosition({ 500, 600 });
	tower_button.setFont(font);
	tower_button.setTextColor(sf::Color::White);

	UI::Button wall_button({ 200, 50 }, "Wall", sf::Color::Green, sf::Color::White, font);
	wall_button.setPosition({ 200, 600 });
	wall_button.setFont(font);
	wall_button.setTextColor(sf::Color::White);

	UI::Button door_button({ 200, 50 }, "Door", sf::Color::Magenta, sf::Color::White, font);
	door_button.setPosition({ 750, 600 });
	door_button.setFont(font);
	door_button.setTextColor(sf::Color::White);

	//Button tracker
	bool buttonClicked = false;

	// Highlight state
	int highlightX = -1, highlightY = -1;
	bool isTroopGridHovered = false;
	int hoveredTroopGridX = -1, hoveredTroopGridY = -1;

	// Fade animation
	bool isTroopGridSelected = false;
	float highlightFade = 0.0f;
	sf::Clock highlightFadeClock;
	int selectedTroopGridX = -1, selectedTroopGridY = -1;


	//Cursor
	sf::Cursor handCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
	sf::Cursor arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();

	//Main game loop
	while (window.isOpen())
	{
		//Clocks
		auto currentTime = deltaClock.restart().asSeconds();
		accumulator += currentTime;



		//Event proceesing
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* resizeEvent = event->getIf<sf::Event::Resized>())
			{
				sf::Vector2f newSize(static_cast<float>(resizeEvent->size.x),
					static_cast<float>(resizeEvent->size.y));
				sf::View view = window.getView();
				view.setSize(newSize);
				view.setCenter(newSize / 2.0f);
				window.setView(view);
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::W)
					up = true;
				else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
					down = true;
				else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
					right = true;
				else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
					left = true;
			}
			else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				if (keyReleased->scancode == sf::Keyboard::Scancode::W) {
					up = false;
				}
				else if (keyReleased->scancode == sf::Keyboard::Scancode::S) {
					down = false;
				}
				else if (keyReleased->scancode == sf::Keyboard::Scancode::D) {
					right = false;
				}
				else if (keyReleased->scancode == sf::Keyboard::Scancode::A) {
					left = false;
				}
			}
			else if (const auto* mouse = event->getIf<sf::Event::MouseWheelScrolled>()) {
				float delta = mouse->delta;
				terrain.setTileSize(terrain.getTileSize() + delta);
				// Update the tileSize
				if (terrain.getTileSize() <= 10.0) terrain.setTileSize(10.0);
				GameFunctions::EntitySpawning::snapTroopsToGrid(troops, terrain.getTileSize());
				GameFunctions::EntitySpawning::snapBuildingsToGrid(buildings, terrain.getTileSize());
			}
			else if (const auto* mouse = event->getIf<sf::Event::MouseMoved>())
			{

				window.setMouseCursor(arrowCursor);
				const auto& obstacleGrid = terrain.getObstacleGrid();
				if (GameFunctions::GridHighlight::getHighlightedTileX() >= 0 && GameFunctions::GridHighlight::getHighlightedTileY() >= 0 && GameFunctions::GridHighlight::getHighlightedTileX() < static_cast<int>(obstacleGrid.size()) && GameFunctions::GridHighlight::getHighlightedTileY() < static_cast<int>(obstacleGrid[GameFunctions::GridHighlight::getHighlightedTileX()].size())) {
					isObstacle = obstacleGrid[GameFunctions::GridHighlight::getHighlightedTileX()][GameFunctions::GridHighlight::getHighlightedTileY()];
				}
				else {
					isObstacle = false;
				}

				color = isObstacle ? sf::Color(255, 0, 0, 200) : sf::Color(255, 255, 255, 100);

				//highlight if not placing and no button is clicked
				if (currentPlacementMode == PlacementMode::None && !buttonClicked) {
					GameFunctions::GridHighlight::calculateHighlightCoordinate(window, terrain, camera);
					int gridX = GameFunctions::GridHighlight::getHighlightedTileX();
					int gridY = GameFunctions::GridHighlight::getHighlightedTileY();

					// checking for troop on this grid
					isTroopGridHovered = false;
					for (const auto& troop : troops) {
						if (troop->getGridX() == gridX && troop->getGridY() == gridY) {
							isTroopGridHovered = true;
							hoveredTroopGridX = gridX;
							hoveredTroopGridY = gridY;
							break;
						}
					}
					if (!isTroopGridHovered) {
						hoveredTroopGridX = -1;
						hoveredTroopGridY = -1;
					}
				}


				// Troop buttons hover
				if (melee_button.isMouseOver(window)) {
					melee_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					melee_button.setBackColor(sf::Color::Blue);
				}

				if (archer_button.isMouseOver(window)) {
					archer_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					archer_button.setBackColor(sf::Color::Blue);
				}

				if (miner_button.isMouseOver(window)) {
					miner_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					miner_button.setBackColor(sf::Color::Blue);
				}

				if (tank_button.isMouseOver(window)) {
					tank_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					tank_button.setBackColor(sf::Color::Blue);
				}

				// Building buttons hover
				if (mainbase_button.isMouseOver(window)) {
					mainbase_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					mainbase_button.setBackColor(sf::Color::Blue);
				}

				if (tower_button.isMouseOver(window)) {
					tower_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					tower_button.setBackColor(sf::Color::Yellow);
				}

				if (wall_button.isMouseOver(window)) {
					wall_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					wall_button.setBackColor(sf::Color::Green);
				}

				if (door_button.isMouseOver(window)) {
					door_button.setBackColor(sf::Color::Black);
					window.setMouseCursor(handCursor);
				}
				else {
					door_button.setBackColor(sf::Color::Magenta);
				}

				if (GameFunctions::GridHighlight::getHighlightGridState())
				{
					GameFunctions::GridHighlight::calculateHighlightCoordinate(window, terrain, camera);
				}
			}
			else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mouse->button == sf::Mouse::Button::Left) {
					buttonClicked = false;



					// Troop button clicks
					if (melee_button.isMouseOver(window)) {
						melee_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createTroops(window, camera, TroopEntities::TroopType::Melee, troops, terrain.getTileSize());
						buttonClicked = true;
					}
					else if (archer_button.isMouseOver(window)) {
						archer_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createTroops(window, camera, TroopEntities::TroopType::Ranged, troops, terrain.getTileSize());
						buttonClicked = true;
					}
					else if (miner_button.isMouseOver(window)) {
						miner_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createTroops(window, camera, TroopEntities::TroopType::Miner, troops, terrain.getTileSize());
						buttonClicked = true;
					}
					else if (tank_button.isMouseOver(window)) {
						tank_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createTroops(window, camera, TroopEntities::TroopType::Tank, troops, terrain.getTileSize());
						buttonClicked = true;
					}

					// Building button clicks
					else if (mainbase_button.isMouseOver(window)) {
						mainbase_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createBuildings(window, camera, BuildingEntities::BuildingType::MainBase, buildings, terrain.getTileSize());
						buttonClicked = true;
					}
					else if (tower_button.isMouseOver(window)) {
						tower_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createBuildings(window, camera, BuildingEntities::BuildingType::Tower, buildings, terrain.getTileSize());
						buttonClicked = true;
					}
					else if (wall_button.isMouseOver(window)) {
						wall_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createBuildings(window, camera, BuildingEntities::BuildingType::Wall, buildings, terrain.getTileSize());
						buttonClicked = true;
					}
					else if (door_button.isMouseOver(window)) {
						door_button.setBackColor(sf::Color(70, 70, 70, 70));
						GameFunctions::EntitySpawning::createBuildings(window, camera, BuildingEntities::BuildingType::Door, buildings, terrain.getTileSize());
						buttonClicked = true;
					}

					//PathFinding
					int gridX = GameFunctions::GridHighlight::getHighlightedTileX();
					int gridY = GameFunctions::GridHighlight::getHighlightedTileY();

					// Recalculate isObstacle for the clicked tile
					const auto& obstacleGrid = terrain.getObstacleGrid();
					isObstacle = false;
					if (gridX >= 0 && gridY >= 0 && gridX < static_cast<int>(obstacleGrid.size()) && gridY < static_cast<int>(obstacleGrid[gridX].size())) {
						isObstacle = obstacleGrid[gridX][gridY];
					}

					// Check if clicking on a troop for selection
					bool clickedOnTroop = false;
					for (size_t i = 0; i < troops.size(); ++i) {
						if (troops[i]->getGridX() == gridX && troops[i]->getGridY() == gridY) {
							clickedOnTroop = true;
							isTroopGridSelected = true;
							selectedTroopIndex = static_cast<int>(i);
							selectedTroopGridX = gridX;
							selectedTroopGridY = gridY;
							highlightFade = 0.0f;
							highlightFadeClock.restart();
							std::cout << "[DEBUG] Troop selected at (" << gridX << ", " << gridY << "), index: " << selectedTroopIndex << std::endl;
							break;
						}
					}

					// try to move the troop
					if (isTroopGridSelected && selectedTroopIndex != -1 && !clickedOnTroop && !isObstacle) {
						auto path = GameFunctions::PathFinding::FindPath(
							troops[selectedTroopIndex]->getGridX(),
							troops[selectedTroopIndex]->getGridY(),
							gridX, gridY,
							terrain.getObstacleGrid()
						);
						if (!path.empty()) {
							troops[selectedTroopIndex]->setPath(path);
							std::cout << "[Troop] Path set from (" << troops[selectedTroopIndex]->getGridX() << ", "
								<< troops[selectedTroopIndex]->getGridY() << ") to ("
								<< gridX << ", " << gridY << "), steps: " << path.size() << "\n";

							// Deselect after move
							isTroopGridSelected = false;
							selectedTroopIndex = -1;
							selectedTroopGridX = -1;
							selectedTroopGridY = -1;
							highlightX = -1;
							highlightY = -1;
						}
						else {
							//display error message if pathfinding fails
							std::cout << "[ERROR] Pathfinding failed from (" << troops[selectedTroopIndex]->getGridX() << ", "
								<< troops[selectedTroopIndex]->getGridY() << ") to ("
								<< gridX << ", " << gridY << ")\n";
						}
					}
				}
				if (mouse->button == sf::Mouse::Button::Right) {
					isTroopGridSelected = false;
					selectedTroopGridX = -1;
					selectedTroopGridY = -1;
					highlightX = -1;
					highlightY = -1;
				}
			}
			else if (const auto* mouse = event->getIf<sf::Event::MouseButtonReleased>())
			{
				if (mouse->button == sf::Mouse::Button::Left) {
					// Troop button releases
					if (melee_button.isMouseOver(window)) {
						melee_button.setBackColor(sf::Color::Black);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Troop;
							currentTroopType = TroopEntities::TroopType::Melee;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}
					else if (archer_button.isMouseOver(window)) {
						archer_button.setBackColor(sf::Color::Black);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Troop;
							currentTroopType = TroopEntities::TroopType::Ranged;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}
					else if (miner_button.isMouseOver(window)) {
						miner_button.setBackColor(sf::Color::Black);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Troop;
							currentTroopType = TroopEntities::TroopType::Miner;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}
					else if (tank_button.isMouseOver(window)) {
						tank_button.setBackColor(sf::Color::Black);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Troop;
							currentTroopType = TroopEntities::TroopType::Tank;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}

					// Building button releases
					else if (mainbase_button.isMouseOver(window)) {
						mainbase_button.setBackColor(sf::Color::Blue);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Building;
							currentBuildingType = BuildingEntities::BuildingType::MainBase;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}
					else if (tower_button.isMouseOver(window)) {
						tower_button.setBackColor(sf::Color::Yellow);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Building;
							currentBuildingType = BuildingEntities::BuildingType::Tower;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}
					else if (wall_button.isMouseOver(window)) {
						wall_button.setBackColor(sf::Color::Green);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Building;
							currentBuildingType = BuildingEntities::BuildingType::Wall;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}
					else if (door_button.isMouseOver(window)) {
						door_button.setBackColor(sf::Color::Magenta);
						if (buttonClicked) {
							currentPlacementMode = PlacementMode::Building;
							currentBuildingType = BuildingEntities::BuildingType::Door;
							GameFunctions::GridHighlight::changeHighlightGridState();
						}
					}

					// troop placement on grid
					else if (GameFunctions::GridHighlight::getHighlightGridState()) {

						if (!isObstacle) {
							if (currentPlacementMode == PlacementMode::Troop) {
								if (!troops.empty()) {
									troops.back()->setGridCoordinates(GameFunctions::GridHighlight::getHighlightedTileX(), GameFunctions::GridHighlight::getHighlightedTileY());
									troops.back()->setPosition(sf::Vector2f(
										GameFunctions::GridHighlight::getHighlightedTileX() * terrain.getTileSize() + terrain.getTileSize() / 2.0f,
										GameFunctions::GridHighlight::getHighlightedTileY() * terrain.getTileSize() + terrain.getTileSize() / 2.0f
									));

									auto* miner = dynamic_cast<TroopEntities::Miner*>(troops.back().get());
									if (miner) {
										int resourceType = terrain.getResourceGrid()[GameFunctions::GridHighlight::getHighlightedTileX()][GameFunctions::GridHighlight::getHighlightedTileY()];
										miner->setResourceType(resourceType);
									}
									GameFunctions::GridHighlight::setHighlightGridState(false);
									currentPlacementMode = PlacementMode::None;
									isTroopGridSelected = false;
									highlightX = -1;
									highlightY = -1;
									hoveredTroopGridX = -1;
									hoveredTroopGridY = -1;
									isTroopGridHovered = false;
								}
							}
							else if (currentPlacementMode == PlacementMode::Building) {
								if (!buildings.empty()) {
									buildings.back()->setGridCoordinates(GameFunctions::GridHighlight::getHighlightedTileX(), GameFunctions::GridHighlight::getHighlightedTileY());
									GameFunctions::GridHighlight::setHighlightGridState(false);
									currentPlacementMode = PlacementMode::None;
									isTroopGridSelected = false;
									highlightX = -1;
									highlightY = -1;
									hoveredTroopGridX = -1;
									hoveredTroopGridY = -1;
									isTroopGridHovered = false;
								}
							}
						}
					}
				}
			}
		}

		// Camera position update
		if (up) {
			if (yMovement > -0.5)
				yMovement -= 0.05;
			else
				yMovement = -0.5;
		}
		if (down) {
			if (yMovement < 0.5)
				yMovement += 0.05;
			else
				yMovement = 0.5;
		}
		if (right) {
			if (xMovement < 0.5)
				xMovement += 0.05;
			else
				xMovement = 0.5;
		}
		if (left) {
			if (xMovement > -0.5)
				xMovement -= 0.05;
			else
				xMovement = -0.5;
		}

		if (!(up || down)) {
			if (yMovement > 0.05)
				yMovement -= 0.05;
			else if (yMovement < -0.05)
				yMovement += 0.05;
			else {
				yMovement = 0;
			}
		}
		if (!(right || left)) {
			if (xMovement > 0.05)
				xMovement -= 0.05;
			else if (xMovement < -0.05)
				xMovement += 0.05;
			else {
				xMovement = 0;
			}
		}
		camera.x += xMovement;
		camera.y += yMovement;
		if (camera.x <= 0.0) camera.x = 0.0, xMovement = 0.0;
		if (camera.y <= 0.0) camera.y = 0.0, yMovement = 0.0;

		if (camera.x >= terrain.getWidth() - (window.getView().getSize().x / terrain.getTileSize()) - 1) {
			camera.x = terrain.getWidth() - (window.getView().getSize().x / terrain.getTileSize()) - 1;
		}
		if (camera.y >= terrain.getHeight() - (window.getView().getSize().y / terrain.getTileSize()) - 1) {
			camera.y = terrain.getHeight() - (window.getView().getSize().y / terrain.getTileSize()) - 1;
		}

		// Update ImGui
		ImGui::SFML::Update(window, sf::seconds(currentTime));
		while (accumulator >= deltaTime)
		{

			while (!oldLocations.empty())
			{
				terrain.setObstacle(oldLocations.back().x, oldLocations.back().y, 0);
				oldLocations.pop_back();
			}

			for (auto& troop : troops)
			{

				terrain.setObstacle(troop->getGridX(), troop->getGridY(), 1);
				oldLocations.push_back({ troop->getGridX(), troop->getGridY() });

				auto* miner = dynamic_cast<TroopEntities::Miner*>(troop.get());
				if (miner) {
					miner->setTimer(miner->getTimer() + deltaTime);
					int resourceType = miner->getResourceType();
					if (miner->getTimer() >= 5.0f && resourceType != 0) {
						if (resourceType == 1) {
							UI::Resources::setWood(miner->getGatherRate());
						}
						else if (resourceType == 2) {
							UI::Resources::setRock(miner->getGatherRate());
						}
						else if (resourceType == 3) {
							UI::Resources::setIron(miner->getGatherRate());
						}
						miner->setTimer(0.0f);
						std::cout << "[Miner] Gathered resources, current resources: "
							<< "Wood: " << UI::Resources::getWood() << ", "
							<< "Rock: " << UI::Resources::getRock() << ", "
							<< "Iron: " << UI::Resources::getIron() << std::endl;
					}
				}
			}

			for (auto& building : buildings)
			{
				terrain.setObstacle(building->getGridX(), building->getGridY(), 1);
				oldLocations.push_back({ building->getGridX(), building->getGridY() });
			}

			for (auto& troop : troops) {
				troop->updatePath(deltaTime, terrain.getTileSize());
				auto* miner = dynamic_cast<TroopEntities::Miner*>(troop.get());
				if (miner) {
					int gridX = miner->getGridX();
					int gridY = miner->getGridY();
					if (gridX >= 0 && gridY >= 0 &&
						gridX < terrain.getWidth() && gridY < terrain.getHeight()) {
						int newResourceType = terrain.getResourceGrid()[gridX][gridY];
						miner->setResourceType(newResourceType);
					}
				}
			}

			accumulator -= deltaTime;
		}

		//Update graphics
		float fps = (currentTime > 0) ? 1.0f / currentTime : 0.0f;
		//std::cout << "FPS: " << fps << std::endl;

		window.clear();

		// highlight fade
		if (isTroopGridSelected) {
			float elapsed = highlightFadeClock.getElapsedTime().asSeconds();
			highlightFade = 0.55f + 0.45f * std::sin(elapsed * 5.0f); // 5.0f = speed
			if (highlightFade < 0.0f) highlightFade = 0.0f;
			if (highlightFade > 1.0f) highlightFade = 1.0f;
		}

		sf::Color highlightColor = sf::Color(0, 255, 0, 100); //green, semi-transparent

		if (isTroopGridSelected && currentPlacementMode != PlacementMode::Building) {
			highlightX = selectedTroopGridX;
			highlightY = selectedTroopGridY;
			highlightColor.a = static_cast<std::uint8_t>(200 * highlightFade);
		}
		else if (isTroopGridHovered && currentPlacementMode != PlacementMode::Building) {
			highlightX = hoveredTroopGridX;
			highlightY = hoveredTroopGridY;
			highlightColor.a = 100;
		}
		else if (GameFunctions::GridHighlight::getHighlightGridState()) {
			highlightX = GameFunctions::GridHighlight::getHighlightedTileX();
			highlightY = GameFunctions::GridHighlight::getHighlightedTileY();
			highlightColor = color;
		}

		// Draw terrain
		terrain.draw(window, camera, highlightX, highlightY, highlightColor);

		//Display
		melee_button.draw(window);
		archer_button.draw(window);
		miner_button.draw(window);
		tank_button.draw(window);
		mainbase_button.draw(window);
		tower_button.draw(window);
		wall_button.draw(window);
		door_button.draw(window);
		GameFunctions::EntitySpawning::spawnTroops(window, camera, troops, terrain);
		GameFunctions::EntitySpawning::spawnBuildings(window, camera, buildings, terrain.getTileSize());
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}