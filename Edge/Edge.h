//
// Created by Akande Adedeji on 2018-12-11.
//

#ifndef MAZE_EDGE_H
#define MAZE_EDGE_H

#include "Arduino.h"

class Edge {
public:
    Edge(Node node, int d, int a);
    Node dest;
    int dist;
    int angle;


#endif //MAZE_EDGE_H
