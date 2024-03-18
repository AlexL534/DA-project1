#ifndef PARSE_H
#define PARSE_H

#include "Reservoir.h"
#include "Station.h"
#include "Pipe.h"
#include "City.h"
#include <vector>

std::vector<Reservoir> parseReservoirs();

std::vector<Station> parseStations();

std::vector<Pipe> parsePipes();

std::vector<City> parseCities();


#endif // PARSE_H