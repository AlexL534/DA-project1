#include "Actions.h"

//Max flow cidade especifica

int Actions::maxFlowSpecificCity(Graph& g, std::string city) {

    int maxFlow = 0;

    g.addVertex("Si", VertexType::CITY, 20000);
    g.addVertex("S", VertexType::RESERVOIR, 10000);

    for (auto it: g.getVertexSet()) {
        if (it->isType(VertexType::CITY) && it->getInfo() != "Si") {
            int demand =(int) cities[it->getId() - 1].getDemand();
            g.addEdge(it->getInfo(), "Si", 1, demand);
        }
    }

    for (auto it: g.getVertexSet()) {
        if (it->isType(VertexType::RESERVOIR) && it->getInfo() != "S") {
            int max = reservoirs[it->getId() - 1].getMaxDelivery();
            g.addEdge("S", it->getInfo(), 1, max);
        }
    }

    g.edmondsKarp("S", "Si");


    Vertex *v = g.findVertex(city);

    for (Edge *edge: v->getPath()) {
        maxFlow += edge->getFlow();
    }
    return maxFlow;
}

map<string, int> Actions::maxFlowAllCities(Graph &g) {
    map<string, int> City_flow;
    for(auto c:cities){
        int flow = maxFlowSpecificCity(g,c.getCode());
        City_flow[c.getCode()] = flow;
    }
    return City_flow;
}


Actions::Actions(vector<Reservoir> reservoirs_, vector<Station> stations_, vector<City> cities_, vector<Pipe> pipes_): reservoirs(reservoirs_), stations(stations_), cities(cities_), pipes(pipes_) {}