#include "Game.h"
#include "TextureManager.h"
#include "Map.h"

#include <sstream>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


bool Game::isRunning = false;
Map* mapObject = new Map();


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{

//SDL STUFF

int flags = 0;

if (fullscreen){
    flags = SDL_WINDOW_FULLSCREEN;
}

if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

    isRunning = true;
}

if (TTF_Init() == -1)
{
	std::cout << "Error : SDL_TTF" << std::endl;
}

//SDL STUFF END

mapObject->tileAtlas = "tile_atlas.png";
mapObject->atlasTexture = TextureManager::LoadTexture(mapObject->tileAtlas);
mapObject->generateMap(25,25);



}


void Game::handleEvents()
{

	SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
		isRunning = false;
    }

}


void Game::update()
{	


//std::cout<< "update LOL!" << std::endl;

}

void Game::render()
{
	SDL_RenderClear(renderer);

	//FILL WITH AUTO CLASSES CONTAINING TEXTURES

	mapObject->renderMap();

	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
