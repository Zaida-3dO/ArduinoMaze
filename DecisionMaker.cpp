//
// Created by f on 12/11/2018.
//

#include "DecisionMaker.h"
#include "vector"


DecisionMaker::makeDecision(Node currentPosition, int botPosition){
    vector<int> possibleDirections;
    currentPosition.visit();
    if(currentPosition.left != nullptr and !currentPosition.left.isVisited()){
        possibleDirections.push_back(resolveDirection(FACE_LEFT));
    }
    if(currentPosition.right != nullptr and !currentPosition.right.isVisited()){
        possibleDirections.push_back(resolveDirection(FACE_RIGHT));
    }
    if(currentPosition.up != nullptr and !currentPosition.up.isVisited()){
        possibleDirections.push_back(resolveDirection(FACE_FORWARD));
    }
    if (possibleDirections.size() == 0) {
        return resolveDirection(botPosition, FACE_BACKWARD);
    }
    //TODO Choose the position to go randomly
}

DecisionMaker::resolveDirection(int botPosition, int turnToDirection){
    return (FACE_LEFT - botPosition < 0) ? (360 + (FACE_LEFT - botPosition)) : FACE_LEFT - botPosition;
}
