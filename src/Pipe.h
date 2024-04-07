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


    /**
     * @brief Get the point A of the pipe
     *
     * @return string
     */
    string getPointA() const;

    /**
     * @brief Get the point B of the pipe
     *
     * @return string
     */
    string getPointB() const;

    /**
     * @brief Get the capacity of the pipe
     *
     * @return int
     */
    int getCapacity() const;

    /**
     * @brief Get the direction of the pipe
     *
     * @return int
     */
    int getDirection() const;

    void setCapacity(int capacity);
};


#endif //WATER_SUPPLY_MANAGEMENT_PIPE_H
