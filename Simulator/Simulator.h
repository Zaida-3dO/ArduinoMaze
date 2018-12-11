//
// Created by Akande Adedeji on 2018-12-11.
//

#ifndef MAZE_SIMULATOR_H
#define MAZE_SIMULATOR_H


class Simulator {
public:
    Simulator();
    void addEdge(int distance, int angle);
    void addNode(bool comp);
    void makeDecision(Node curNode, int botDir);
private:
    Node curNode()
};


#endif //MAZE_SIMULATOR_H
