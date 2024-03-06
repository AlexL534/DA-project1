#include "Station.h"

Station::Station() {
    this->name = "";
    this->code = "";
}

Station::Station(const string &name, const string &code) {
    this->name = name;
    this->code = code;
}

string Station::getName() const {
    return this->name;
}

string Station::getCode() const {
    return this->code;
}
