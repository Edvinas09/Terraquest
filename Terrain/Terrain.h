#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <string>

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
        std::vector<std::vector<int>> grid;

    public:
        //---Constructor---//
        Terrain(int height, int width, int seed);

        //---Destructor---//

        //---Methods---//
        //--Create() to creates a new terrain map--//
        //--Clear() to clear the terrain map--//
        //--Update() to update the terrain maps seed--// 
        void create(int width, int height, int seed);
        void destroy();
        void clear();
        void update(int seed);

        int getHeight();
        int getWidth();
        int getSeed();
        const std::vector<std::vector<int>> getGrid();

        void setSeed(int seed);
        void setHeight(int height);
        void setWidth(int width);
        void setGrid(const std::vector<std::vector<int>> grid);

        void generateTerrain();
        std::string toString();
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