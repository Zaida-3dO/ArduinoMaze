//
// Created by Akande Adedeji on 2018-12-11.
//

#include "Arduino.h"
#include "Simulator.h"
#include "Node.h"

Simulator::Simulator() {
}
Simulator::rewireEdge(int distance, int angle){
    Node node;
    Edge edge(node, distance, angle);
    curNode = node;
}
void Simulator::addNode(){
    curNode = node;
}
void Simulator::addEdge(int distance, int angle) {
    Node node;
    Edge edge(node, distance, angle);
    nod
}