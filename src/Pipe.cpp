#include "Pipe.h"

Pipe::Pipe() {
    this->pointA = "";
    this->pointB = "";
    this->capacity = -1;
    this->direction = -1;
}

Pipe::Pipe(const string &pointA, const string &pointB, const int &capacity, const int &direction) {
    this->pointA = pointA;
    this->pointB = pointB;
    this->capacity = capacity;
    this->direction = direction;
}

string Pipe::getPointA() const {
    return this->pointA;
}

string Pipe::getPointB() const {
    return this->pointB;
}

int Pipe::getCapacity() const {
    return this->capacity;
}

int Pipe::getDirection() const {
    return this->direction;
}
