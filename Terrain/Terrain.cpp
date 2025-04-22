#include "Terrain.h"
#include <sstream>
#include "FastNoiseLite.h"

using namespace TerrainNamespace;

//---Constructor---//
Terrain::Terrain(int height, int width, int seed) : height(height), width(width), seed(seed)
{
    create(width, height, seed);
}
//---Destructor---//
//---CRUD---//
void Terrain::create(int width, int height, int seed)
{
    this->width = width;
    this->height = height;
    this->seed = seed;
    grid.resize(height, std::vector<int>(width, 0));
    generateTerrain();
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
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(0.1f);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float value = noise.GetNoise((float)x, (float)y);
            grid[y][x] = static_cast<int>((value + 1.0f) * 2.5f); // Normalize to 0-5
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