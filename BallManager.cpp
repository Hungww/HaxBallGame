#include "BallManager.h"
#include "Collision.h"
BallManager::BallManager()
{
	int mass = 300;
	Ball* ball = new Ball(471,378,30,1);
	balls.push_back(ball);
	ball->mass = mass;

	
	Ball* ball2 = new Ball(200, 200, 30, 2);
	balls.push_back(ball2);
	ball2->mass = mass;

	Ball* ball3 = new Ball(722, 378, 30, 3);
	balls.push_back(ball3);
	ball3->mass = mass;

	Ball* ball4 = new Ball(400, 400, 30, 4);
	balls.push_back(ball4);
	ball4->mass = mass;

	Ball* ballPlay = new Ball(650, 650, 15, -1);
	ballPlay->mass = 100;

	balls.push_back(ballPlay);
	ballPlay->DOT_HEIGHT = 30;
	ballPlay->DOT_WIDTH = 30;
	selectedBall = ball;
	selectedBall2 = ball3;
	reset();

	//create the edges of the table
	Edge* edge = new Edge(48, 41, 1148, 41, 5,1); //TOP
	edges.push_back(edge);

	Edge* edge2 = new Edge(48, 39, 48, 320, 5,0);//LEFT_TOP
	edges.push_back(edge2);

	Edge* edge3 = new Edge(48, 436, 48, 714, 5,0);//LEFT_BOTTOM
	edges.push_back(edge3);

	Edge* edge4 = new Edge(48, 715, 1148, 715, 5,1);//BOTTOM
	edges.push_back(edge4);

	Edge* edge5 = new Edge(1148, 39, 1148, 320, 5,0);//RIGHT_TOP
	edges.push_back(edge5);
	Edge* edge6 = new Edge(1148, 436, 1148, 714, 5,0);//RIGHT_BOTTOM
	edges.push_back(edge6);

	//Load cursor texture


}

void BallManager::update()
{	
	ballCollisions.clear();
	for (auto& a : balls) {
		for (auto& b : balls) {
			//skip when comparing a ball to itself
			if (a->id == b->id)
				continue;
			//check if balls collide
			if (Collision::DetectCollision(a, b)) {

				bool duplicate = false;
				//create the opposite pairing of balls and check if the opposite pairing is already
				//in the list of collisions
				std::pair<Ball*, Ball*> tempPair;
				tempPair = { b,a };
				for (auto& c : ballCollisions) {
					if (c == tempPair)
						duplicate = true;
				}

				//if the pair isn't a duplicate add it to the ball collision list
				if (!duplicate)
					ballCollisions.push_back({ a,b });
			}
		}
	}

	// go through the ball collision list and handle the elastic collision physics
	for (auto& c : ballCollisions) {
		Collision::DynamicCollision(c.first, c.second);
		//if bullet then delete
		if (c.first->id == 10) {
			balls.erase(std::remove(balls.begin(), balls.end(), c.first), balls.end());

		}
		if (c.second->id == 10) {
			balls.erase(std::remove(balls.begin(), balls.end(), c.second), balls.end());

		}
	}

	//check all balls against all edges
	for (auto& b : balls) {
		for (auto& e : edges) {
			//DetectCollisionEdge returns the closest point on the edge if there is a collision
			Vector2D* collisionPoint = Collision::DetectCollisionEdge(b, e);
			//if collisionPoint isn't a nullptr then that means collision was detected
			if (collisionPoint && (abs(b->velocity.x * b->velocity.x + b->velocity.y * b->velocity.y) > 0.08)) {
				//create a fake temporary ball at the point of collision and store the original ball and the fake ball in a pair
				/*Ball* fakeBall = new Ball(collisionPoint->x, collisionPoint->y, e->radius, -2);
				fakeBall->mass = 100;
				fakeBall->velocity.x = -b->velocity.x;
				fakeBall->velocity.y = -b->velocity.y;*/
				//edgeCollisions.push_back({ b,fakeBall });
				if(e->isLongEdge==1 && b->id==-1)
					b->velocity.y= -b->velocity.y;
				else if(e->isLongEdge==0 && b->id==-1)
					b->velocity.x = -b->velocity.x;
				if(b->id==10)
					balls.erase(std::remove(balls.begin(), balls.end(), b), balls.end());
			}
		}
	}

	//handle the ball to edge collisions
	for (auto& c : edgeCollisions) {
		Collision::DynamicCollision(c.first, c.second);
	}


	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->update();
	}
	std::cout<<balls[4]->velocity.x<<" "<<balls[4]->velocity.y<<std::endl;
}

void BallManager::render()
{
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->render();
	}
	cursorTexture1->render(selectedBall->position.x - 17.5, selectedBall ->position.y -70);
	cursorTexture2->render(selectedBall2->position.x - 17.5, selectedBall2->position.y - 70);
}

void BallManager::reset()
{
	Ball* ball= nullptr;
	ball=getBallbyID(1);
	ball->position.x = 471;
	ball->position.y = 378;
	ball->velocity.x = 0;
	ball->velocity.y = 0;

	ball=getBallbyID(2);
	ball->position.x = 50+40;
	ball->position.y = 377;
	ball->velocity.x = 0;
	ball->velocity.y = 0;

	ball=getBallbyID(3);
	ball->position.x = 722;
	ball->position.y = 378;
	ball->velocity.x = 0;
	ball->velocity.y = 0;

	ball=getBallbyID(4);
	ball->position.x = 1144-40;
	ball->position.y = 377;
	ball->velocity.x = 0;
	ball->velocity.y = 0;

	ball = getBallbyID(-1);
	ball->position.x = 598;
	ball->position.y = 378;
	ball->velocity.x = 0;
	ball->velocity.y = 0;
	ballCollisions.clear();
	edgeCollisions.clear();
	balls[4]->velocity.x = 0;
	balls[4]->velocity.y = 0;

	selectedBall = getBallbyID(1);
	selectedBall2 = getBallbyID(3);



}

Ball* BallManager::changeBall()
{	selectedBall->velocity= { 0,0 };
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i] == selectedBall)
		{
			switch (balls[i]->id)
			{
			case 1:
				selectedBall = getBallbyID(2);
				return selectedBall;
				break;
			case 2:
				selectedBall = getBallbyID(1);
				return selectedBall;
				break;
			default:
				break;
			}
		}
	}
	return nullptr;
}

Ball* BallManager::changeBall2()
{	selectedBall2->velocity = { 0,0 };
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i] == selectedBall2)
		{
			switch (balls[i]->id)
			{
			case 3:
				selectedBall2 = getBallbyID(4);
				return selectedBall2;
				break;
			case 4:
				selectedBall2 = getBallbyID(3);
				return selectedBall2;
				break;
			default:
				break;
			}
		}
	}
	return nullptr;
	return nullptr;
}

Ball* BallManager::getBallbyID(int ID)
{	
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i]->id == ID)
			return balls[i];
	}
	return nullptr;
}
