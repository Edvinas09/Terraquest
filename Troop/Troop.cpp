#include "Troop.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <stdexcept>

#include <memory>
#include <stdexcept>
#include <map>
#include <iostream>

using namespace TroopEntities;

std::map<TroopType, sf::Texture> Troop::troopTextures;
bool Troop::texturesLoaded = false;

std::unique_ptr<Troop> TroopCreator::createTroop(TroopType type, const sf::Vector2f& spawnPosition) {
    if (!Troop::isTexturesLoaded()) {
        Troop::loadTextures();
    }

    switch (type) {
    case TroopType::Melee:
        return std::make_unique<Melee>(100, 20, 100, spawnPosition);
    case TroopType::Ranged:
        return std::make_unique<Ranged>(80, 15, 100, 5, spawnPosition);
    case TroopType::Miner:
        return std::make_unique<Miner>(60, 10, 100, 3, spawnPosition);
    case TroopType::Tank:
        return std::make_unique<Tank>(200, 30, 50, 50, spawnPosition);
    default:
        throw std::invalid_argument("Invalid troop type");
    }
}

void Troop::loadTextures() {
    std::vector<std::pair<TroopType, std::string>> files = {
        {TroopType::Melee, "resources/images/Swordsman.png"},
        {TroopType::Ranged, "resources/images/Archer.png"},
        {TroopType::Miner, "resources/images/Miner.png"},
        {TroopType::Tank, "resources/images/Brute.png"},
    };

    for (const auto& [type, path] : files) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << std::endl;
        }
        else {
            troopTextures[type] = texture;
        }
    }

    texturesLoaded = true;
}

void Troop::updatePath(float deltaTime, float tileSize) {
    if (path.empty()) return;
    sf::Vector2f target = sf::Vector2f(path.front().x * tileSize + tileSize / 2.0f, path.front().y * tileSize + tileSize / 2.0f);
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float moveStep = speed * deltaTime;
    if (distance < moveStep) {
        setGridCoordinates(path.front().x, path.front().y);
        position = target;
        path.erase(path.begin());
    }
    else {
        direction /= distance;
        position += direction * moveStep;
    }
}
void Troop::draw(sf::RenderWindow& window, const sf::Vector2f& position, float tilesize) {
    TroopType type;

    if (dynamic_cast<Melee*>(this)) {
        type = TroopType::Melee;
    }
    else if (dynamic_cast<Ranged*>(this)) {
        type = TroopType::Ranged;
    }
    else if (dynamic_cast<Miner*>(this)) {
        type = TroopType::Miner;
    }
    else if (dynamic_cast<Tank*>(this)) {
        type = TroopType::Tank;
    }
    else {
        type = TroopType::Melee;
    }

    if (troopTextures.find(type) != troopTextures.end()) {
        sf::Sprite sprite(troopTextures[type]);

        sf::Vector2u textureSize = troopTextures[type].getSize();
        sprite.setOrigin({ textureSize.x / 2.0f, textureSize.y / 2.0f });

        float scaleX = tilesize / textureSize.x;
        float scaleY = tilesize / textureSize.y;
        float scale = std::min(scaleX, scaleY) * 1.0f; 

        if (type == TroopType::Tank) {
            scale = std::min(scaleX, scaleY) * 1.2f;
        }
        sprite.setScale({ scale, scale });

        sprite.setPosition(position);
        window.draw(sprite);
    }
}
