#ifndef WATER_SUPPLY_MANAGEMENT_CITY_H
#define WATER_SUPPLY_MANAGEMENT_CITY_H

#include <string>

using namespace std;

class City {
private:
    string name;
    int id;
    string code;
    float demand;
    int population;

public:
    City();

    City(
            const string &name,
            const int &id,
            const string &code,
            const float &demand,
            const int &population
    );

    string getName() const;
    int getId() const;
    string getCode() const;
    double getDemand() const;
    int getPopulation() const;
};


#endif //WATER_SUPPLY_MANAGEMENT_CITY_H
