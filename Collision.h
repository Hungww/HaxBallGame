#pragma once
#include "Main.h"
#include "Ball.h"
#include "Edge.h"
class Collision
{
public:
    static bool DetectCollision(Ball* b1, Ball* b2);
    //static bool DetectCollisionHole(Ball* b, Hole* h);
    static Vector2D* DetectCollisionEdge(Ball* b, Edge* e);
    static void DynamicCollision(Ball* b1, Ball* b2);


};

