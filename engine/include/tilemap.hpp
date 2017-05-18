#ifndef __ENGINE_TILEMAP__
#define __ENGINE_TILEMAP__

#include <string>
#include <vector>
#include "components/image.hpp"
#include "tileset.hpp"
#include "vector.hpp"

namespace engine {

class TileMap : public GameObject {
public:

    TileMap(std::string image_path, std::string map_path, int width, int height, std::string game_object_name,int _x,int _y);
        
    virtual ~TileMap();

    bool init();
    void setTileSet(TileSet *tileset);
    int& at(int x, int y, int z);
    void renderLayer(int layer, int camera_x = 0, int camera_y = 0);
    bool draw();

private:
    std::vector<int> tile_matrix;
    int map_depth;
    int map_height;
    int map_width;
    TileSet *m_tileset;
    std::string m_map_path;
};

}

#endif