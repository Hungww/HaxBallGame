#pragma once
#include "Main.h"
#include "Ball.h"
#include <vector>
#include "Edge.h"
class BallManager
{
	public:
	BallManager();
	~BallManager();
	void update();
	void render();
	void reset();
	Ball* changeBall();
	Ball* changeBall2();
	Ball* selectedBall = nullptr;
	Ball* selectedBall2 = nullptr;
	int score1 = 0;
	int score2 = 0;
	int bulletCount1 = 3;
	int bulletStartID=-10;
	bool bulletRender=0;
	LTexture* cursorTexture1;
	LTexture* cursorTexture2;

	std::vector<Ball*> balls;
	std::vector<Edge*> edges;
	Ball* getBallbyID(int ID);
	std::vector<std::pair<Ball*, Ball*>> ballCollisions;
	std::vector<std::pair<Ball*, Ball*>> edgeCollisions;
};

