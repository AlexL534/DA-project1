#ifndef PARSE_H
#define PARSE_H

#include "Reservoir.h"
#include "Station.h"
#include "Pipe.h"
#include "City.h"
#include <vector>
#include <map>

std::vector<Reservoir> parseReservoirs();

std::vector<Station> parseStations();

std::vector<Pipe> parsePipes();

std::vector<City> parseCities();

map<std::string, std::string> createCityCodeMap(const std::vector<City>& cities);
#endif // PARSE_H