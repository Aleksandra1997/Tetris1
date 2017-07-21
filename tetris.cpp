#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <conio.h>
#include "game.h"

using namespace std;


int print()
{
	int value;

	cout << "Witaj!" << endl;
	cout << "Zapraszam do wyprobowania gry Tetris" << endl;
	cout << "Udanej rozgrywki!" << endl;
	cout << endl;
	cout << "--------------------MENU--------------------" << endl;

	cout << "[1] - Nowa gra" << endl;
	cout << "[2] - Koniec" << endl;
	cin >> value;
	return value;
}

int main(int argc, char* args[])
{
	int menu;
	menu = print();

	if (menu == 1)
	{
		Game game;
		game.logic();
		game.End();
	}
	else
	{
		return 0;
	}
}