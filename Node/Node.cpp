//
// Created by Akande Adedeji on 2018-12-11.
//

#include "Node.h"
#include "Arduino.h"

const TOP_EDGE = 0;
const LEFT_EDGE = 270;
const RIGHT_EDGE = 90;
const BOTTOM_EDGE = 180;
Node::Node() {
    visited = false;
    touched = false;
    left = nullptr;
    right = nullptr;
    up = nullptr;
    down = nullptr;
}

void Node::visit(){
    visited = true;
}

void Node::touched(){
    visited = true;
}

bool Node::isVisited(){
    return visited;
}

bool Node::isTouched() {
    return touched
}

Edge Node::getEdge(int dir){
    if (dir == TOP_EDGE){
        return up;
    }else if (dir == LEFT_EDGE){
        return left;
    } else if (dir == RIGHT_EDGE){
        return right;
    } else if (dir == BOTTOM_EDGE){
        return down;
    }
}

Edge Node::setEdge(int dir, Edge edge){
    if (dir == TOP_EDGE){
        return up;
    }else if (dir == LEFT_EDGE){
        return left;
    } else if (dir == RIGHT_EDGE){
        return right;
    } else if (dir == BOTTOM_EDGE){
        return down;
    }
}