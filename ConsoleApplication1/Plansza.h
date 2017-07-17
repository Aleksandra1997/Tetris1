#pragma once
#include <SDL.h>
#include "Block.h"

class Plansza
{
public:
	Plansza();
	void draw(SDL_Renderer *renderer);
	enum{Width = 17,Height = 18};
	bool Collision(Block &t1);
	void IsDown(Block &t1);
	void DeleteLines(int &wynik);

private:
	int matrix[Width][Height]; //do rysowania planszy
};