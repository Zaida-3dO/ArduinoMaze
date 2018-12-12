//
// Created by f on 12/11/2018.
//

#ifndef MAZE_DECISIONMAKER_H
#define MAZE_DECISIONMAKER_H


class DecisionMaker {
public:
    int makeDecision(Graph graph, Node position, int botPosition);


private:
    const int FACE_LEFT = 270;
    const int FACE_RIGHT = 90;
    const int FACE_FORWARD = 0;
    const int FACE_BACKWARD = 180;
    int resolveDirection(int botPosition, int turnToDirection);
};


#endif //MAZE_DECISIONMAKER_H
