//
// Created by Akande Adedeji on 2018-12-11.
//

#ifndef MAZE_NODE_H
#define MAZE_NODE_H

#include "Arduino.h"

class Node {
public:
    Node();
    void visit();
    void touch();
    void isTouched();
    bool isVisited();
    Edge getEdge(int dir);
    Edge setEdge(int dir, Edge edge);

private:
    bool visited;
    bool touched;
    Edge left;
    Edge right
    Edge up;
    Edge down;
};


#endif //MAZE_NODE_H
