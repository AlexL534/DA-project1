#ifndef PARSE_H
#define PARSE_H

#include "Reservoir.h"
#include "Station.h"
#include "Pipe.h"
#include "City.h"
#include <vector>
#include <map>
/**
 * @brief Parse the Reservoirs from the Reservoir.csv file
 *
 * @return std::vector<Reservoir>
 */
std::vector<Reservoir> parseReservoirs();
/**
 * @brief Parse the Stations from the Stations.csv file
 *
 * @return std::vector<Station>
 */
std::vector<Station> parseStations();
/**
 * @brief Parse the Pipes from the Pipes.csv file
 *
 * @return std::vector<Pipe>
 */
std::vector<Pipe> parsePipes();
/**
 * @brief Parse the Cities from the Cities.csv file
 *
 * @return std::vector<City>
 */
std::vector<City> parseCities();
/**
 * @brief Create a map with the city name as the key and the city code as the value
 *
 * @param cities
 * @return std::map<std::string, std::string>
 */
std::map<std::string, std::string> createCityNameMap(const std::vector<City>& cities);
#endif // PARSE_H