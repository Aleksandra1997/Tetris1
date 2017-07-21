#include "Block.h"
#include <SDL.h>

//konstruktor
Block::Block(Type type, int x, int y)
{
	type_ = type;
	x_ = x;
	y_ = y;
	angle_ = 0;
}

void Block::move_next(int dx, int dy)
{
	x_ += dx;
	y_ += dy;
}

void Block::draw(SDL_Renderer *renderer)
{
	switch (type_)
	{
	case I:
	{
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		break;
	}
	case J:
	{
		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
		break;
	}
	case L:
	{
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
		break;
	}
	case O:
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x7f, 0xff);
		break;
	}
	case S:
	{
		SDL_SetRenderDrawColor(renderer, 0xff, 0x7f, 0x00, 0xff);
		break;
	}
	case T:
	{
		SDL_SetRenderDrawColor(renderer, 0x7f, 0x40, 0x00, 0xff);
		break;
	}
	case Z:
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x7f, 0x7f, 0xff);
		break;
	}
	}
	for (auto x = 0; x < 4; ++x)
	{
		for (auto y = 0; y < 4; ++y)
		{
			if (Shape(x, y))
			{
				SDL_Rect rect{ (x + x_) * 720 / 2 / 10 + 1, (y + y_) * 720 / 2 / 10 + 1, 720 / 2 / 10 - 2, 720 / 2 / 10 - 2 };
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}
void Block::move(int dx, int dy)
{
	x_ += dx;
	y_ += dy;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Shape(i, j))
			{
				if ((x_ + i < 1) || (x_ + i > 16)) //jesli wyjdzie poza wymiar bloku
				{
					x_ -= dx;
				}
				if ((y_ < 0) || (y_ + j > 18))
				{
					y_ -= dy;
				}
			}
		}
	}
}
void Block::rotate()
{
	++angle_;
	angle_ %= 4;
}
bool Block::Shape(int posX, int posY)
{
	static const char* Shapes[][4] = {
		{
			" *  "
			" *  "
			" *  "
			" *  ", //I
			"    "
			"****"
			"    "
			"    ",
			" *  "
			" *  "
			" *  "
			" *  ",
			"    "
			"****"
			"    "
			"    ",
		},
		{
			"  * "
			"  * "
			" ** "
			"    ",//J
			"    "
			"*   "
			"*** "
			"    ",
			" ** "
			" *  "
			" *  "
			"    ",
			"    "
			"    "
			"*** "
			"  * ",
		},
		{
			" *  "
			" *  "
			" ** "
			"    ",//L
			"    "
			"*** "
			"*   "
			"    ",
			" ** "
			"  * "
			"  * "
			"    ",
			"  * "
			"*** "
			"    "
			"    ",
		},
		{
			"    "
			" ** "
			" ** "
			"    ", //O
			"    "
			" ** "
			" ** "
			"    ",
			"    "
			" ** "
			" ** "
			"    ",
			"    "
			" ** "
			" ** "
			"    ",
		},
		{
			"    "
			" ** "
			"**  "
			"    ",//S
			" *  "
			" ** "
			"  * "
			"    ",
			"    "
			" ** "
			"**  "
			"    ",
			" *  "
			" ** "
			"  * "
			"    ",
		},
		{
			"    "
			"*** "
			" *  "
			"    ",//T
			" *  "
			"**  "
			" *  "
			"    ",
			" *  "
			"*** "
			"    "
			"    ",
			" *  "
			" ** "
			" *  "
			"    ",
		},
		{
			"    "
			"**  "
			" ** "
			"    ",//Z
			"  * "
			" ** "
			" *  "
			"    ",
			"    "
			"**  "
			" ** "
			"    ",
			"  * "
			" ** "
			" *  "
			"    ",
		},
	};
	return Shapes[type_][angle_][posX + posY * 4] == '*'; // typ do rysowania/  kat/  wspolrzedne do rysowania
	//zwraca ksztalt danego klocka i odpoiednie wymary poprzez wymiary
}

int Block::positionX()
{
	return x_;
}
int Block::positionY()
{
	return y_;
}