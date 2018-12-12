//
// Created by Akande Adedeji on 2018-12-11.
//

#include "Edge.h"
#include "Arduino.h"

Edge::Edge(Node n, int d, int a) {
    node = n;
    dist = d;
    angle = a;
}