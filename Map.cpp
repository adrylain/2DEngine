#pragma once

#include "Map.h"
#include <noise/noise.h>
#include <iostream>
#include <cmath>

using namespace noise;

void Map::generateMap(int x, int y)
{

    this->mapDimensions = Vector2D(x,y);

    module::Perlin myModule;


    for (int ny = 0; ny < y; ny++) {
        for (int nx = 0; nx < x; nx++) {

            double value = myModule.GetValue(nx, ny, 0.5)*10;

            this->mapData.push_back(value);


        }
    }

    std::cout << "Finished generating " << x << "x" << y << " grid." << std::endl;

}






void Map::renderMap(){

    int maxY = this->mapDimensions.y;
    int maxX = this->mapDimensions.x;

    for (auto it = this->mapData.begin(); it != this->mapData.end(); ++it) {
        int index = std::distance(this->mapData.begin(), it);
        int nx = index % maxX;
        int ny = index / maxY;

        int spriteNumber = *it;


        if (spriteNumber < 0) {
            spriteNumber = 0;
        }else if (spriteNumber > 1) {
            spriteNumber = 1;
        }

            int tileSize = 32;

            SDL_Rect srcrect = { spriteNumber * 64, 0, 64, 64 };
            SDL_Rect dstrect = { nx*tileSize, ny*tileSize, tileSize, tileSize };
            TextureManager::Draw(this->atlasTexture, srcrect, dstrect,SDL_FLIP_NONE);


    }


}





