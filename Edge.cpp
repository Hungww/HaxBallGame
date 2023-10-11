#include "Edge.h"
Edge::Edge(float pos1x, float pos1y, float pos2x, float pos2y, float r, bool longedge) {

    position1.x = pos1x;
    position1.y = pos1y;
    position2.x = pos2x;
    position2.y = pos2y;
    radius = r;
    isLongEdge = longedge;


}

void Edge::update() {


}