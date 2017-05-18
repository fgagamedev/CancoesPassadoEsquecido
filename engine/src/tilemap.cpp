#include "tilemap.hpp"
#include "tileset.hpp"
#include "vector.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include "log.h"

using namespace engine;

TileMap::TileMap(std::string image_path, std::string map_path, int width, int height,
        std::string game_object_name,int _x,int _y){
	m_name = game_object_name;
	xF = (int)_x;
	yF = (int)_y;
	m_map_path = map_path;
	m_state = State::enabled;
	TileSet tileset(width, height, *this, image_path, 0, 0);
	setTileSet(&tileset);
	add_component(tileset);
	//Aqui ta mais enabled
    if(m_tileset->state() == Component::State::enabled)
    	INFO("OOOOOOOOOOOOOOOOOOOOOOOOOO");
}

TileMap::~TileMap(){
	delete(m_tileset);
}

bool TileMap::init(){
	//Aqui ja nao ta mais enabled
    if(m_tileset->state() == Component::State::enabled)
    	INFO("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	INFO("Init Tilemap");

	std::fstream f(m_map_path, f.in);

	if(not f.is_open()){
		exit(1);
	}else{
		std::string s;
		getline(f, s);

		std::stringstream ss;
		ss << s;

		ss >> map_width;
		ss.ignore(2, ',');

		ss >> map_height;
		ss.ignore(2, ',');

		ss >> map_depth;
		ss.ignore(2, ',');

		while(getline(f, s)){
			ss.clear();
			ss << s;

			int index;
			while(ss >> index){
				tile_matrix.emplace_back(--index);

				ss.ignore(2, ',');
			}
		}
	}

	GameObject::init();

	return true;
}

void TileMap::setTileSet(TileSet *tSet){
	m_tileset = tSet;
}

int &TileMap::at(int x, int y, int z){
	int index = (y * map_width + x) + (z * map_width * map_height);
	return tile_matrix[index];
}

void TileMap::renderLayer(int layer, int camera_x, int camera_y){
	for(int y = 0; y < map_height; y++){
		for(int x = 0; x < map_width; x++){
			m_tileset->render(at(x, y, layer), x * m_tileset->getWidth() + camera_x, 
			y * m_tileset->getHeight() + camera_y);
		}
	}
}

bool TileMap::draw(){
	INFO("Draw Tilemap");
	for(int layer = 0; layer < map_depth; layer++){
		renderLayer(layer, 0, 0);
	}

	return true;
}