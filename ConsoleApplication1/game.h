#pragma once
#include <SDL.h>
#include "Block.h"
#include "Plansza.h"
#include <cstdlib>

class Game
{
public:
	void logic();
	Game();
	void End();
	bool Load();
	void CheckCollision(Block &s1);

private:
	SDL_Window *window_;
	SDL_Renderer *renderer_;

	SDL_Surface *message;
	SDL_Texture *text;
	SDL_Rect textRect;
	SDL_Color black;

	SDL_Surface *scoreSurface;
	SDL_Texture *points;
	SDL_Rect scoreRect;

	SDL_Surface *timerSurface;
	SDL_Texture *time;
	SDL_Rect timeRect;

	SDL_Surface *blockSurface;
	SDL_Texture *blockTexture;
	SDL_Rect blockRect;

	Plansza plansza;

	Block::Type losowo = static_cast<Block::Type>(rand() % 7);
	Block::Type next_ = static_cast<Block::Type>(rand() % 7);
	Block block_ = Block(losowo, 7, 0);
	Block next = Block(next_, 20, 13);
};