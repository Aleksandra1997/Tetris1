#pragma once
#include <SDL.h>

class Block
{
public:
	enum Type{I = 0 ,J,L,O,S,T,Z};
	Block(Type,int x,int y);
	void draw(SDL_Renderer *renderer);
	void move(int x, int y);
	void rotate();
	bool Shape(int posX, int posY);
	int positionX();
	int positionY();
	void move_next(int dx, int dy);

private:
	int x_;
	int y_;
	Type type_;
	int angle_;

};