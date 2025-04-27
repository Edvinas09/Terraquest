#include "Terrain.h"
#include <sstream>
#include <iostream>
#include "FastNoiseLite.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace TerrainNamespace;

//---Constructor---//
Terrain::Terrain(int height, int width, int seed) : height(height), width(width), seed(seed)
{
    create(width, height, seed);
    this->tile_size = 5.0;

}
//---Destructor---//
//---CRUD---//
void Terrain::create(int width, int height, int seed)
{
    grid.resize(height, std::vector<int>(width, 0));
    generateTerrain();
    loadTextures();
}
void Terrain::destroy()
{
    grid.clear();
    height = 0;
    width = 0;
    seed = 0;
}
void Terrain::update(int seed)
{
    this->seed = seed;
}
void Terrain::loadTextures() {
    std::vector<std::string> files = { "Terrain/Textures/Water.png", "Terrain/Textures/Dirt.png",
                                       "Terrain/Textures/Hill.png", "Terrain/Textures/Mountain.png" };
    for (std::string file : files) {
        sf::Texture texture;
        if (!texture.loadFromFile(file)) {
            std::exit(1);
        }
        textures.push_back(texture);
    }
}
void Terrain::draw(sf::RenderWindow& window, sf::Vector2<float> camera, int highlightedTileX, int highlightedTileY) {
    sf::Vector2<unsigned int> dimensions = window.getSize();
    float window_width = dimensions.x;
    float window_height = dimensions.y;
    float tile = (1920 / window_width) * this->tile_size;
    float scale = tile / 500.0f;
     for (int x = (int)camera.x; (x-1 - (int)camera.x < (window_width / tile)) && (grid.size()-1 > x); x+=1.0) {
         for (int y = (int)camera.y; (y-1 - (int)camera.y < (window_height / tile)) && (grid[x].size()-1 > y); y+=1.0) {
             try {
                 sf::Sprite sprite(textures[grid[x][y]]);
                 sprite.setScale({ scale, scale });
                 sf::Vector2<float> size(tile * (x - camera.x), tile * (y - camera.y));
                 sprite.setPosition(size);
                 window.draw(sprite);
                 if (x == highlightedTileX && y == highlightedTileY)
                 {
					 float outlineThickness = 3.0f;
					 sf::RectangleShape outline(sf::Vector2f(tile, tile));
                     outline.setPosition({ size.x - outlineThickness, size.y - outlineThickness });
					 outline.setFillColor(sf::Color(0, 0, 0, 0));
					 outline.setOutlineThickness(outlineThickness);
					 outline.setOutlineColor(sf::Color(255, 255, 255, 100));
					 window.draw(outline);
                 }
             }
             catch (...) {

             }
         }
     }
}

std::string Terrain::toString()
{
    std::stringstream oss;
    oss << "Terrain: ";
    oss << height << "X" << width << ", Seed: " << seed << "\n";
    return oss.str();
}
//--Methods-- //
void Terrain::generateTerrain()
{
    FastNoiseLite noise;
    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.04f);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float value = noise.GetNoise((float)x, (float)y);
            grid[y][x] = static_cast<int>((value + 1.0f) * 2.0f); // Normalize to 0-5
        }
    }
}
//--Getters--//
int Terrain::getHeight()
{
    return height;
}
int Terrain::getWidth()
{
    return width;
}
int Terrain::getSeed()
{
    return seed;
}
float Terrain::getTileSize() 
{
    return tile_size;
}
const std::vector<std::vector<int>> Terrain::getGrid()
{
    return grid;
}
//--Setters--//
void Terrain::setHeight(int height)
{
    this->height = height;
}
void Terrain::setWidth(int width)
{
    this->width = width;
}
void Terrain::setSeed(int seed)
{
    this->seed = seed;
}
void Terrain::setGrid(std::vector<std::vector<int>> grid)
{
    this->grid = grid;
}
void Terrain::setTileSize(float size) {
    this->tile_size = size;
}