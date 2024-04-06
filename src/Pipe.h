#ifndef WATER_SUPPLY_MANAGEMENT_PIPE_H
#define WATER_SUPPLY_MANAGEMENT_PIPE_H

#include <string>

using namespace std;

class Pipe {
private:
    string pointA;
    string pointB;
    int capacity;
    int direction;

public:
    Pipe();

    Pipe(
            const string &pointA,
            const string &pointB,
            const int &capacity,
            const int &direction
    );

    string getPointA() const;

    string getPointB() const;

    int getCapacity() const;

    int getDirection() const;

    void setCapacity(int capacity);
};


#endif //WATER_SUPPLY_MANAGEMENT_PIPE_H
