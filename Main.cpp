/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "Main.h"
#include "LTexture.h"
#include "Ball.h"
#include "BallManager.h"


//Screen dimension constants
 int SCREEN_WIDTH = 1200;
 int SCREEN_HEIGHT = 755;

//Texture wrapper class


//The application time based timer
class LTimer
{
public:
	//Initializes variables
	LTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};

//The dot that will move around on the screen


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
BallManager* ballManager = new BallManager();
//Scene textures
LTexture* gTexture= new LTexture();
LTexture gTextTexture;

//Globally used font
TTF_Font* gFont = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	//for each ball in ballManager
	for (int i = 0; i < ballManager->balls.size(); i++)
	{	
		if (ballManager->balls[i]->id != -1) {
			//Load dot texture
			if (ballManager->balls[i]->id == 1 || ballManager->balls[i]->id == 2) {
				if (!ballManager->balls[i]->gBallTexture.loadFromFile("team1.png"))
				{
					printf("Failed to load dot texture!\n");
					success = false;
				}
			}
			else
			{
				if (!ballManager->balls[i]->gBallTexture.loadFromFile("team2.png"))
				{
					printf("Failed to load dot texture!\n");
					success = false;
				}
			}
		}
		else {
			//Load dot texture
			if (!ballManager->balls[i]->gBallTexture.loadFromFile("ball.png"))
			{
				printf("Failed to load dot texture!\n");
				success = false;
			}
		}


	}
	//Load background texture
	if (!gTexture->loadFromFile("background.jpg"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("sport.ttf", 40);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gTextTexture.loadFromRenderedText("0 - 0", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	//Load cursor texture
	ballManager->cursorTexture1 = new LTexture();
	if (!ballManager->cursorTexture1->loadFromFile("red.png"))
	{
		printf("Failed to load cursor texture!\n");
		success = false;
	}
	ballManager->cursorTexture2 = new LTexture();
	if (!ballManager->cursorTexture2->loadFromFile("blue.png"))
	{
		printf("Failed to load cursor texture!\n");
		success = false;
	}


	return success;
}

void close()
{
	//Free loaded images
	

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	gTextTexture.free();
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

std::string s;
int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{	
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			
			
			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//if press tab then change the ball1
					if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
					{
						if (e.key.keysym.sym == SDLK_TAB)
						{
							ballManager->changeBall();
						}
					}
					//if press enter then change the ball2
					if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
					{
						if (e.key.keysym.sym == SDLK_KP_ENTER)
						{
							ballManager->changeBall2();
						}
					}


					//Handle input for the dot
					ballManager->selectedBall->handleEvent(e);
					ballManager->selectedBall2->handleEvent2(e);
					
					
				}

				//Move the dot
				//ballManager->balls[0]->move();
				//render a jpg image
				
				
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				
				SDL_RenderClear(gRenderer);

				//Render objects
				gTexture->render(0, 0);
				s= std::to_string(ballManager->score1) + " - " + std::to_string(ballManager->score2);
				gTextTexture.loadFromRenderedText(s, { 0, 0, 0 });
				gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, 5);
				//(SCREEN_HEIGHT - gTextTexture.getHeight()) / 2
				ballManager->update();
				ballManager->render();
				//std::cout << ballManager->balls[0]->velocity.x << std::endl;
				//std::cout << ballManager->balls[0]->velocity.y << std::endl;
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	std::cout<< ballManager->balls[0]->position.x << std::endl;
	std::cout << ballManager->balls[0]->position.y << std::endl;
	close();

	return 0;
}
