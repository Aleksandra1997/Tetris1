#include "Plansza.h"
#include <SDL.h>
#include <iostream>

Plansza::Plansza()
{
	for (int i = 1; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			matrix[i][j] = 1;//wypelnienie planszy wartosciami 1
		}
	}
}
void Plansza::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	for (auto x = 1; x < Width; ++x)
	{
		for (auto y = 0; y < Height; ++y)
		{
			if (matrix[x][y] == 1)
			{
				SDL_RenderDrawPoint(renderer, x * 900 / 2 / 10 + 900 / 2 / 10 / 2, y * 900 / 2 / 10 + 900 / 2 / 10 / 2);
			}
			else
			{
				SDL_Rect rect{ x * 720 / 2 / 10, y * 720 / 2 / 10, 720 / 2 / 10, 720 / 2 / 10 }; //polozenie x, polozenie y, szerokosc prostokata, wysokosc prostokata
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}
bool Plansza::Collision(Block &t1)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (t1.Shape(i, j)) //tworzy sie klocek i jego ksztalt -- >mozna okreslic wymiar
			{
				int pX = t1.positionX() + i;
				int pY = t1.positionY() + j;

				if ((pY < 0) || (pY > 17))//tylko kolizja z dolem ma byc, aby pojawial sie nastepny klocek
				{
					return true;
				}
				//if ((pX < 1) || (pX >16))//kolizja z lewej i prawej strony
				//{
				//	return true;
				//}
				if (matrix[pX][pY] == 0) // gdy na planszy sa zapisane juz jakies klocki
				{
					return true;
				}
			}
		}
	}
	return false;
}
void Plansza::IsDown(Block &t1)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (t1.Shape(i, j)) //tworzy sie klocek i jego ksztalt -- >mozna okreslic wymiar
			{
				int pX = t1.positionX() + i;
				int pY = t1.positionY() + j;
				matrix[pX][pY] = 0; //dane klocki wypelniamy 0
			}
		}
	}
}
void Plansza::DeleteLines(int &wynik)
{
	for (int k = Height - 1; k > 0; k--)
	{
		bool full = true;
		int i = 1;//odkad zaczyna
		while (i < 17 )//gdzie konczy
		{
			if (matrix[i][k] == 1)//gdy rzad nie jest zapelniony
			{
				full = false;
				break;
			}
			else i++;
		}
		if (full)
		{
			wynik += 100;
			for (int j = k - 1; j >= 0; j--)
			{
				for (int i = 0; i < Width; i++)
				{
					matrix[i][j + 1] = matrix[i][j];
				}
			}
			for (int x = 0; x < Width; x++)
			{
				matrix[x][0] = 1;
			}
		}
	}
}