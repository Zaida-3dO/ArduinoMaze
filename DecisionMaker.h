//
// Created by opsij on 11/12/2018.
//

#ifndef MAZE_DECISIONMAKER_H
#define MAZE_DECISIONMAKER_H


class DecisionMaker {
public:
    char makeDecision(Graph graph, Node position, int botPosition);

private:
    const char LEFT = 'L';
    const char RIGHT = 'R';
    const char UP = 'U';
    const char DOWN = 'D';
};


#endif //MAZE_DECISIONMAKER_H
