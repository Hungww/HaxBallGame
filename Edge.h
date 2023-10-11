#pragma once
#include "Main.h"
class Edge {

public:

    Edge(float pos1x, float pos1y, float pos2x, float pos2y, float r, bool longedge);
    bool isLongEdge;
    void printID();
    void draw();
    void update();



    Vector2D position1;
    Vector2D position2;
    
    float radius;

};

