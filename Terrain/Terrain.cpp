#include "Terrain.h"
#include <sstream>
#include <FastNoiseLite.h>

using namespace TerrainNamespace;

class Terrain 
{
    private:
        int height;
        int width;
        int seed;
        std::vector<std::vector<int>> grid;
    public:

        //---Constructor---//
        Terrain(int height, int width, int seed):
            height(height), width(width), seed(seed) {
                create(width, height, seed);
            }
        //---Destructor---//
        ~Terrain() = default;

        //---CRUD---//
        void create(int width, int height, int seed) {
            this->width = width;
            this->height = height;
            this->seed = seed;
            grid.resize(height, std::vector<int>(width, 0));
        }
        void destroy() {
            grid.clear();
            height = 0;
            width = 0;
            seed = 0;
        }
        void update(int seed) {
            this->seed = seed;
        }
        std::string toString() const {
            std::stringstream oss;
            oss << "Terrain: ";
            oss << height << "X" << width << ", Seed: " << seed << "\n";
            return oss.str();
        }

    //--Methods--//
    private:
        void generateTerrain() {
            FastNoiseLite noise;
            noise.SetSeed(seed);
            noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
            noise.SetFrequency(0.1f);

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    float value = noise.GetNoise((float)x, (float)y);
                    grid[y][x] = static_cast<int>((value + 1.0f) * 2.5f); // Normalize to 0-5
                }
            }
        }
    public:
        //--Getters--//
        int getHeight() const {
            return height;
        }
        int getWidth() const {
            return width;
        }
        int getSeed() const {
            return seed;
        }
        const std::vector<std::vector<int>>& getGrid() const {
            return grid;
        }
        //--Setters--//
        void setHeight(int height) {
            this->height = height;
        }
        void setWidth(int width) {
            this->width = width;
        }
        void setSeed(int seed) {
            this->seed = seed;
        }
        void setGrid(const std::vector<std::vector<int>>& grid) {
            this->grid = grid;
        }
};