#ifndef WATER_SUPPLY_MANAGEMENT_STATION_H
#define WATER_SUPPLY_MANAGEMENT_STATION_H

#include <string>

using namespace std;

class Station {
public:
    string name;
    string code;

private:
    Station();

    Station(
            const string &name,
            const string &code
    );

    string getName() const;
    string getCode() const;
};


#endif //WATER_SUPPLY_MANAGEMENT_STATION_H
