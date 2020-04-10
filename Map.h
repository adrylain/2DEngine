#pragma once

#include "Vector2D.h"
#include "TextureManager.h"
#include <vector>


class Map {

public:

int getTileSize() { return tileSize; }
Vector2D getMapDimensions() { return mapDimensions; }
void generateMap(int x, int y);
void renderMap();

SDL_Texture *atlasTexture;
const char* tileAtlas;
int tileSize;
Vector2D mapDimensions;

std::vector<double> mapData;



};
