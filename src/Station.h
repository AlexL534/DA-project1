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

    /**
     * @brief Get the id of the station
     *
     * @return int
     */
    int getId() const;
    /**
     * @brief Get the code of the station
     *
     * @return string
     */
    string getCode() const;
};


#endif //WATER_SUPPLY_MANAGEMENT_STATION_H
