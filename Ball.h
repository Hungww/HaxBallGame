#pragma once
#include "Main.h"
#include "LTexture.h"


class Ball
{
public:
	//The dimensions of the dot
	 int DOT_WIDTH = 60;
	 int DOT_HEIGHT = 60;
	 int boost = 1;
	//Maximum axis velocity of the dot
	 int DOT_VEL = 1.5;

	//Initializes the variables
	Ball();
	Ball(float posx, float posy, float r, int ID, const char* texturePath = nullptr);

	~Ball();


	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);
	void handleEvent2(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render();
	//Update 
	void update();
public:
	Vector2D position;
	Vector2D texPos;
	Vector2D velocity;
	bool isColliding = false;
	float radius;
	int id;
	bool isBoosted=false;
	float mass = 100;
	
	LTexture gBallTexture;
};

