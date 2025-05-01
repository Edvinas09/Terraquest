#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Terrain/Terrain.h"
#include "UI.hpp"
#include "Troop/Troop.hpp"
#include "GameFunctions.hpp"

#include <iostream>

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

    //Font for the game
    sf::Font font;
    font.openFromFile("fonts/arial.ttf");


    //Camera
    sf::Vector2<float> camera = { 0, 0 };
    bool up = false, down = false, left = false, right = false;
    float xMovement = 0.0, yMovement = 0.0;


    //Terrain
    TerrainNamespace::Terrain terrain(200, 200, 2);
    float tileSize = terrain.getTileSize();

    //Troops
    std::vector<std::unique_ptr<TroopEntities::Troop>> troops;
    sf::Vector2f troopPosition;

    //Button
    UI::Button button({ 200, 50 }, "Test", sf::Color::Red, sf::Color::White, font);
    button.setPosition({ 500, 100 });
    button.setFont(font);
    button.setTextColor(sf::Color::White);

    //Cursor
    sf::Cursor handCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
    sf::Cursor arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();

    //Event
    while (window.isOpen()) {
        //Clocks
        auto currentTime = deltaClock.restart().asSeconds();
        accumulator += currentTime;
        //Event proceesing
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
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
                GameFunctions::EntitySpawning::snapTroopsToGrid(troops, tileSize);
            }
            else if (const auto* mouse = event->getIf<sf::Event::MouseMoved>())
            {
                if (button.isMouseOver(window))
                {
                    button.setBackColor(sf::Color::Black);
                    window.setMouseCursor(handCursor);
                }
                else
                {
                    button.setBackColor(sf::Color::Blue);
                    window.setMouseCursor(arrowCursor);
                }
                if (GameFunctions::GridHighlight::getHighlightGridState())
                {
                    GameFunctions::GridHighlight::calculateHighlightCoordinate(window, terrain, camera);

                }
                else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouse->button == sf::Mouse::Button::Left) {
                        if (button.isMouseOver(window))
                        {
                            button.setBackColor(sf::Color(70, 70, 70, 70));

                            GameFunctions::EntitySpawning::createTroops(window, camera, troops, tileSize);

                        }
                    }
                    else if (const auto* mouse = event->getIf<sf::Event::MouseButtonReleased>())
                    {
                        if (mouse->button == sf::Mouse::Button::Left) {
                            if (button.isMouseOver(window))
                            {
                                button.setBackColor(sf::Color::Black);
                                GameFunctions::GridHighlight::changeHighlightGridState();

                            }
                            else if (GameFunctions::GridHighlight::getHighlightGridState())
                            {

                                GameFunctions::GridHighlight::setHighlightGridState(false);
                            }
                        }
                    }
                }

                //Camera position update
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


                while (accumulator >= deltaTime) {
                    //Update your game logic here, updates vyks reciau negu frames, dabar 20/sec

                    accumulator -= deltaTime;
                }

                //Update graphics
                float fps = (currentTime > 0) ? 1.0f / currentTime : 0.0f;
                //std::cout << "FPS: " << fps << std::endl;

                //Terrain
                terrain.draw(window, camera, GameFunctions::GridHighlight::getHighlightGridState() ? GameFunctions::GridHighlight::getHighlightedTileX() : -1, GameFunctions::GridHighlight::getHighlightGridState() ? GameFunctions::GridHighlight::getHighlightedTileX() : -1);


                //Display window
                ImGui::SFML::Render(window);
                button.draw(window);
                GameFunctions::EntitySpawning::spawnTroops(window, camera, troops, tileSize);
                window.display();
                window.clear();
            }

            ImGui::SFML::Shutdown();
        }
    }
}
