#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "parse.h"
#include "Pipe.h"
#include "menu.h"
#include "graph.h"


int main() {
    std::vector<Reservoir> reservoirs = parseReservoirs();
    std::vector<Station> stations = parseStations();
    std::vector<Pipe> pipes = parsePipes();
    std::vector<City> cities = parseCities();

    menu();

    return 0;
}