#ifndef WATER_SUPPLY_MANAGEMENT_RESERVOIR_H
#define WATER_SUPPLY_MANAGEMENT_RESERVOIR_H

#include <string>

using namespace std;

class Reservoir {
public:
    string name;
    string municipality;
    int id;
    string code;
    int maxDelivery;

private:
    Reservoir();

    Reservoir(
        const string &name,
        const string &municipality,
        const int &id,
        const string &code,
        const int &maxDelivery
    );

    string getName() const;
    string getMunicipality() const;
    int getId() const;
    string getCode() const;
    int getMaxDelivery() const;
};


#endif //WATER_SUPPLY_MANAGEMENT_RESERVOIR_H
