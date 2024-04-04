#ifndef WATER_SUPPLY_MANAGEMENT_ACTIONS_H
#define WATER_SUPPLY_MANAGEMENT_ACTIONS_H


#include <map>
#include "graph.h"
#include "City.h"
#include "Station.h"
#include "Pipe.h"
#include "Reservoir.h"
#include "parse.h"

class Actions {

    vector<Reservoir> reservoirs;
    vector<Station> stations;
    vector<City> cities;
    vector<Pipe> pipes;

    Graph graph;

public:
    Actions(vector<Reservoir> reservoirs_, vector<Station> stations_, vector<City> cities_, vector<Pipe> pipes_);
    int maxFlowSpecificCity(Graph& g, string city); //2.1
    map<string, int> maxFlowAllCities(Graph& g); //2.1
    void balanceAndCalculateMetrics(Graph& g); //2.3
    void analyzePumpingStations(Graph& g); //3.2
    void crucialPipelines(Graph& g); //3.3
    struct AffectedCity {
        string code; // Código da cidade
        int deficit; // Déficit no fornecimento de água para a cidade
    };
};


#endif
