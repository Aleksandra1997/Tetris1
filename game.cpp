#include "game.h"
#include "Block.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 670;

Mix_Music *gMusic = NULL;
Mix_Chunk *gCollision = NULL;
TTF_Font *gFont = NULL;

int score = 0;

SDL_Rect wall_left, wall_right, wall_down, rectangle, puste1;
Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) != 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	//tworzy okno 
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &window_, &renderer_);

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

}
void Game::End()
{
	SDL_FreeSurface(message);
	message = NULL;

	SDL_FreeSurface(scoreSurface);
	scoreSurface = NULL;

	SDL_FreeSurface(timerSurface);
	timerSurface = NULL;

	SDL_FreeSurface(blockSurface);
	blockSurface = NULL;

	//Music
	Mix_FreeChunk(gCollision);
	gCollision = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	SDL_DestroyTexture(text);
	SDL_DestroyTexture(points);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}
void SetObjects()
{
	wall_left.x = 27;
	wall_left.y = 0;
	wall_left.w = 10;
	wall_left.h = SCREEN_HEIGHT;

	wall_right.x = SCREEN_WIDTH - 290;
	wall_right.y = 0;
	wall_right.w = 10;
	wall_right.h = SCREEN_HEIGHT;

	wall_down.x = 27;
	wall_down.y = SCREEN_HEIGHT - 23;
	wall_down.w = SCREEN_WIDTH - 290;
	wall_down.h = 23;

	rectangle.x = SCREEN_WIDTH - 280;
	rectangle.y = 0;
	rectangle.w = 280;
	rectangle.h = SCREEN_HEIGHT;

	puste1.x = 0;
	puste1.y = 0;
	puste1.w = 27;
	puste1.h = SCREEN_HEIGHT;
}
void Game::CheckCollision(Block &s1)
{
	if (plansza.Collision(s1)) //jesli jest kolizja to pojawia siê nastepny klocek
	{
		Mix_PlayChannel(-1, gCollision, 0);
		score += 50;
		plansza.IsDown(block_);
		plansza.DeleteLines(score);
		//block_ = next;
		block_ = Block(next_, 7, 0); //nastepny klocek sie losuje	
		next_ = static_cast<Block::Type>(rand() % 7);//zmiana klocka nastepnego
		next = Block(next_, 20, 13);

		if (plansza.Collision(block_))
		{
			//tworzymy od nowa plansze
			plansza = Plansza();
			score = 0;
		}
	}
	else //brak kolizji
	{
		block_ = s1;
	}
}
bool Game::Load()
{
	bool success = true;

	gFont = TTF_OpenFont("tekst.ttf", 50);
	black = { 0, 0, 0 };
	message = TTF_RenderText_Solid(gFont, "Punkty: ", black);
	blockSurface = TTF_RenderText_Solid(gFont, "Nastepny blok", black);


	gMusic = Mix_LoadMUS("music.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gCollision = Mix_LoadWAV("medium.wav");
	if (gCollision == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}
void Game::logic()
{
	//glowna petla gry
	bool run = true;
	SDL_Event event;
	unsigned int finish, start = SDL_GetTicks();
	unsigned int startTime = 0;
	SetObjects();

	if (Load())
	{
		Mix_PlayMusic(gMusic, -1);

		while (run)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					run = false;
				}

				//wcisniecie klawisza
				else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
					{
						block_.rotate();
						block_.move(0, 0);
						break;
					}
					case SDLK_LEFT:
					{
						Block t = block_;
						t.move(-1, 0);
						CheckCollision(t);
						break;
					}
					case SDLK_RIGHT:
					{
						Block t = block_;
						t.move(1, 0);
						CheckCollision(t);
						break;
					}
					case SDLK_DOWN:
					{
						Block t = block_;
						t.move(0, 1);
						CheckCollision(t);
						break;
					}
					case SDLK_ESCAPE:
						exit(0);
					}
				}
				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_DOWN:
					{
						Block t = block_;
						t.move(0, 1);
						CheckCollision(t);
						break;
					}
					case SDLK_ESCAPE:
						exit(0);
					}
				}
			}

			SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff); //ustawia na kolor bialy
			SDL_RenderClear(renderer_);
			plansza.draw(renderer_);

			//sciany
			SDL_SetRenderDrawColor(renderer_, 154, 146, 146, 0xFF);
			SDL_RenderFillRect(renderer_, &wall_left);
			SDL_RenderDrawRect(renderer_, &wall_left);
			SDL_RenderFillRect(renderer_, &wall_right);
			SDL_RenderDrawRect(renderer_, &wall_right);
			SDL_RenderFillRect(renderer_, &wall_down);
			SDL_RenderDrawRect(renderer_, &wall_down);

			//prostokat lewa i prawa strona 
			SDL_SetRenderDrawColor(renderer_, 196, 40, 40, 0xFF);
			SDL_RenderFillRect(renderer_, &rectangle);
			SDL_RenderDrawRect(renderer_, &rectangle);
			SDL_RenderFillRect(renderer_, &puste1);
			SDL_RenderDrawRect(renderer_, &puste1);

			next.draw(renderer_);
			block_.draw(renderer_); //bedziemy tutaj zapisywac nasze klocki

			text = SDL_CreateTextureFromSurface(renderer_, message);
			textRect.x = 670;
			textRect.y = 50;
			SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

			//punkty
			string score_text = to_string(score);
			scoreSurface = TTF_RenderText_Solid(gFont, score_text.c_str(), black);
			points = SDL_CreateTextureFromSurface(renderer_, scoreSurface);
			scoreRect.x = 670;
			scoreRect.y = 110;
			SDL_QueryTexture(points, NULL, NULL, &scoreRect.w, &scoreRect.h);

			//time
			string timer = "Czas gry: " + to_string(startTime);
			timerSurface = TTF_RenderText_Solid(gFont, timer.c_str(), black);
			time = SDL_CreateTextureFromSurface(renderer_, timerSurface);
			timeRect.x = 660;
			timeRect.y = 250;
			SDL_QueryTexture(time, NULL, NULL, &timeRect.w, &timeRect.h);

			//klocki
			blockTexture = SDL_CreateTextureFromSurface(renderer_, blockSurface);
			blockRect.x = 645;
			blockRect.y = 380;
			SDL_QueryTexture(blockTexture, NULL, NULL, &blockRect.w, &blockRect.h);


			finish = SDL_GetTicks();
			if (finish > start)
			{
				/*start += 1000;*/
				if (startTime > 10)
				{
					start += 500;
				}
				else if (startTime > 20)
				{
					start += 100;
				}
				else if (startTime > 35)
				{
					start += 50;
				}
				else
				{
					start += 1000;
				}
				startTime += 1000 / 1000.0f;
				Block t = block_;
				t.move(0, 1);
				CheckCollision(t);
			}
			SDL_RenderCopy(renderer_, text, NULL, &textRect);
			SDL_RenderCopy(renderer_, points, NULL, &scoreRect);
			SDL_RenderCopy(renderer_, time, NULL, &timeRect);
			SDL_RenderCopy(renderer_, blockTexture, NULL, &blockRect);
			SDL_RenderPresent(renderer_);
		}
	}
}