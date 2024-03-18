#include "Station.h"

Station::Station() {
    this->id = -1;
    this->code = "";
}

Station::Station(const int &id, const string &code) {
    this->id = id;
    this->code = code;
}

int Station::getId() const {
    return this->id;
}

string Station::getCode() const {
    return this->code;
}
