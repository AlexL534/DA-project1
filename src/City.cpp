#include "City.h"

City::City() {
    this->name = "";
    this->id = -1;
    this->code = "";
    this->demand = -1;
    this->population = -1;
}

City::City(const string &name, const int &id, const string &code, const float &demand, const int &population) {
    this->name = name;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

string City::getName() const {
    return this->name;
}

int City::getId() const {
    return this->id;
}

string City::getCode() const {
    return this->code;
}

double City::getDemand() const {
    return this->demand;
}

int City::getPopulation() const {
    return this->population;
}
