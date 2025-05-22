#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <string>
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//---NameSpace for Terrain---//
namespace TerrainNamespace {
    //--Terrain class--//
    class Terrain
    {
    private:
        //--Private variables--//
        //-Height, Width of the generated map-//
        //-Seed for random terrain generation-//
        //-Grid for storing the generated map-//
        int height;
        int width;
        int seed;
        float tile_size;
        std::vector<sf::Texture> textures;
        std::vector<std::vector<int>> grid;
        std::vector<std::vector<int>> resourceGrid;
        std::vector<std::vector<bool>> obstacleGrid;

    public:
        //---Constructor---//
        Terrain(int height, int width, int seed);

        //---Destructor---//

        //---Methods---//
        //--Create() to creates a new terrain map--//
        //--Clear() to clear the terrain map--//
        //--Update() to update the terrain maps seed--// 
        void destroy();
        void clear();
        void update(int seed);
        void draw(sf::RenderWindow&, sf::Vector2<float>, int highlightedTileX, int highlightedTileY);

        int getHeight();
        int getWidth();
        int getSeed();
        float getTileSize();
        const std::vector<std::vector<int>> getGrid();
        const std::vector<std::vector<bool>> getObstacleGrid();
        const std::vector<std::vector<int>> getResourceGrid();

        void setSeed(int seed);
        void setHeight(int height);
        void setWidth(int width);
        void setTileSize(float size);
        void setGrid(const std::vector<std::vector<int>> grid);
        void setObstacle(int x, int y, bool value);

        std::string toString();

    private:
        void create(int width, int height, int seed);
        void loadTextures();
        void generateTerrain();
    };
}
#endif // TERRAIN_H

//--- Custom exception class ---//
#ifndef TERRAINEXCEPTION_H
#define TERRAINEXCEPTION_H

#include <stdexcept>
#include <string>

namespace TerrainNamespace
{
    class TerrainException : public std::exception {
        private:
            std::string msg;
        public:
            TerrainException(const std::string& message);
            const char* what() const noexcept override;
    };
}
#endif