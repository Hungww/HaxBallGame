#include "Ball.h"
#include "LTexture.h"
#include "BallManager.h"
extern BallManager* ballManager;

extern  int SCREEN_WIDTH;
extern  int SCREEN_HEIGHT;
Ball::Ball()
{
	//Initialize the offsets
	texPos.x = 0;
	texPos.y = 0;

	position.x = texPos.x + DOT_WIDTH / 2;
	position.y = texPos.y + DOT_HEIGHT / 2;

	//Initialize the velocity
	velocity.x = 0;
	velocity.y = 0;
	radius = DOT_WIDTH / 2;
	id = -2;
}

Ball::Ball(float posx, float posy, float r, int ID, const char* texturePath)
{
	//Initialize the offsets
	id = ID;
	position.x = posx;
	position.y = posy;
	radius = r;

	texPos.x = position.x - radius;
	texPos.y = position.y - radius;


	//Initialize the velocity
	velocity.x = 0;
	velocity.y = 0;
	radius = r;
	id = ID;
	if (texturePath != nullptr)
	{
		gBallTexture.loadFromFile(texturePath);
	}

}

void Ball::handleEvent(SDL_Event& e){

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{	
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		//if press A then boost
		case SDLK_LSHIFT:
			if (isBoosted == false) {
				boost=3;
				isBoosted = true;
				velocity.x *= boost;
				velocity.y *= boost;
			}
			break;
		case SDLK_w: velocity.y -= DOT_VEL*boost; break;
		case SDLK_s: velocity.y += DOT_VEL * boost; break;
		case SDLK_a: velocity.x -= DOT_VEL * boost; break;
		case SDLK_d: velocity.x += DOT_VEL * boost; break;
		//if press space then shoot
		case SDLK_SPACE:
			
				if (ballManager->bulletCount1 > 0) {
					ballManager->bulletCount1--;
					ballManager->bulletStartID = this->id;
					Ball* playBall= ballManager->getBallbyID(-1);
					Vector2D* temp = new Vector2D(playBall->position.x- position.x, playBall->position.y - position.y);
					temp->Normalize();
					Ball* bullet;
					if(position.x<playBall->position.x)
						bullet = new Ball(position.x, position.y,15 , 10, "redb.png");
						
					else
						bullet = new Ball(position.x , position.y, 15, 10, "redb.png");
					bullet->DOT_HEIGHT = 30;
					bullet->DOT_WIDTH = 30;
					bullet->mass = 500;
					bullet->velocity.x = temp->x * 3;
					bullet->velocity.y = temp->y*3;
					ballManager->balls.push_back(bullet);
				}
			
			break;
		case SDLK_ESCAPE: ballManager->reset(); break;
		//if press shift then boost

			
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LSHIFT:
			if (isBoosted == true) {
				boost = 1;
				isBoosted = false;
			}
			break;
		/*case SDLK_UP: velocity.y += DOT_VEL * boost; break;
		case SDLK_DOWN: velocity.y -= DOT_VEL * boost; break;
		case SDLK_LEFT: velocity.x += DOT_VEL * boost; break;
		case SDLK_RIGHT: velocity.x -= DOT_VEL * boost; break;*/
		//if release shift then stop boost
		case SDLK_w: velocity.y = 0; break;
		case SDLK_s: velocity.y = 0; break;
		case SDLK_a: velocity.x = 0; break;
		case SDLK_d: velocity.x = 0; break;

			
		}
	}
}

void Ball::handleEvent2(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			//if press A then boost
		case SDLK_RSHIFT:
			if (isBoosted == false) {
				boost = 3;
				isBoosted = true;
			}
			break;
		case SDLK_UP: velocity.y -= DOT_VEL * boost; break;
		case SDLK_DOWN: velocity.y += DOT_VEL * boost; break;
		case SDLK_LEFT: velocity.x -= DOT_VEL * boost; break;
		case SDLK_RIGHT: velocity.x += DOT_VEL * boost; break;
			//if press shift then boost


		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_RSHIFT:
			if (isBoosted == true) {
				boost = 1;
				isBoosted = false;
			}
			break;
			/*case SDLK_UP: velocity.y += DOT_VEL * boost; break;
			case SDLK_DOWN: velocity.y -= DOT_VEL * boost; break;
			case SDLK_LEFT: velocity.x += DOT_VEL * boost; break;
			case SDLK_RIGHT: velocity.x -= DOT_VEL * boost; break;*/
			//if release shift then stop boost
		case SDLK_UP: velocity.y = 0; break;
		case SDLK_DOWN: velocity.y = 0; break;
		case SDLK_LEFT: velocity.x = 0; break;
		case SDLK_RIGHT: velocity.x = 0; break;


		}
	}
}

void Ball::move()
{	
	if (id == -1) {
		velocity.x *= 0.997;
		velocity.y *= 0.997;
}


	//clamp the velocity to zero to avoid the ball moving very slowly for a long time
	if (abs(velocity.x * velocity.x + velocity.y * velocity.y) < 0.1)
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	//Move the dot left or right
	position.x += velocity.x;

	//If the dot went too far to the left or right
	if ((position.x  < 40) || (position.x   > SCREEN_WIDTH-40))
	{
		//Move back
		//position.x -= velocity.x;
		if(position.x<40)
			ballManager->score2++;
		else
			ballManager->score1++;
		ballManager->reset();
		
	}

	//Move the dot up or down
	position.y += velocity.y;

	//If the dot went too far up or down
		if ((position.y  < 0) || (position.y   > SCREEN_HEIGHT))
	{
		//Move back
		//position.y -= velocity.y;
		//velocity.y = -velocity.y;
		
	}


	texPos.x = position.x - DOT_WIDTH / 2;
	texPos.y = position.y - DOT_HEIGHT / 2;
}

void Ball::render()
{
	//Show the dot
	gBallTexture.render(texPos.x, texPos.y);
}

void Ball::update()
{	
	move();
	
}

Ball::~Ball()
{
	gBallTexture.free();
}