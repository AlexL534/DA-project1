#ifndef WATER_SUPPLY_MANAGEMENT_STATION_H
#define WATER_SUPPLY_MANAGEMENT_STATION_H

#include <string>

using namespace std;

class Station {
private:
    int id;
    string code;

public:
    Station();

    Station(
            const int &id,
            const string &code
    );

    int getId() const;
    string getCode() const;
};


#endif //WATER_SUPPLY_MANAGEMENT_STATION_H
