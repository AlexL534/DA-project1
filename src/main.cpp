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

    /*Daqui para baixo está a dar casota <----------
    Graph<std::string> graph;

    for (const auto& reservoir : reservoirs) {
        graph.addVertex(reservoir.getCode());
    }

    for (const auto& station : stations) {
        graph.addVertex(station.getCode());
    }

    for (const auto& city : cities) {
        graph.addVertex(city.getCode());
    }


    for (const auto& pipe : pipes) {
        if (pipe.getDirection() == 0 ) {
            graph.addBidirectionalEdge(pipe.getPointA(),pipe.getPointB(),pipe.getCapacity());
        }
        else if (pipe.getDirection() == 1) {
            graph.addEdge(pipe.getPointA(),pipe.getPointB(),pipe.getCapacity());
        }
    }
    */
    menu();

    return 0;
}