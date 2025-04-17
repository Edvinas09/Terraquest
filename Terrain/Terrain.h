#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>

//---NameSpace for Terrain---//
namespace TerrainNamespace{
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
        ~Terrain();

        //---Methods---//
        //--Create() to creates a new terrain map--//
        //--Clear() to clear the terrain map--//
        //--Update() to update the terrain maps seed--// 
        void create(int width, int height, int seed);
        void clear();
        void update(int seed);
        int getHeight() const;
        int getWidth() const;
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