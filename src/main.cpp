#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "parse.h"
#include "Pipe.h"
#include "menu.h"
#include "Actions.h"

int main() {

    std::vector<Reservoir> reservoirs = parseReservoirs();
    std::vector<Station> stations = parseStations();
    std::vector<Pipe> pipes = parsePipes();
    std::vector<City> cities = parseCities();

    Actions a(reservoirs, stations, cities, pipes);

    Graph g, graph;

    graph = g.buildGraph(reservoirs, stations, pipes, cities);

    map<string, int> aaa = a.maxFlowAllCities(graph);

    for(auto it : aaa){
        cout << endl << it.first << ' ' << it.second << endl;
    }



    //menu();


    return 0;
}