#include "Actions.h"
#include <cmath>
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


    g.removeVertex("Si");
    g.removeVertex("S");

    return maxFlow;
}

map<string, int> Actions::maxFlowAllCities(Graph& g) {
    map<string, int> City_flow;
    for(auto c:cities){
        int flow = maxFlowSpecificCity(g,c.getCode());
        City_flow[c.getCode()] = flow;
    }
    return City_flow;
}


Actions::Actions(vector<Reservoir> reservoirs_, vector<Station> stations_, vector<City> cities_, vector<Pipe> pipes_): reservoirs(reservoirs_), stations(stations_), cities(cities_), pipes(pipes_) {}

void Actions::balanceAndCalculateMetrics(Graph& g) {
    //edmonds-karp
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

    // Calculate initial metrics
    vector<int> diff;
    int orig_max_diff = INT_MIN;
    int sum = 0, count = 0;
    double orig_average = 0, orig_variance = 0;

    // Iterate over all vertices in the graph
    for (Vertex* v : g.getVertexSet()) {
        if (v->getInfo() != "S" && v->getInfo() != "Si") {
            // Iterate over all edges adjacent to the current vertex
            for (Edge *e: v->getAdj()) {
                int d = e->getCapacity() - e->getFlow();
                diff.push_back(d);
                sum += d;
                count++;
                if (d > orig_max_diff) {
                    orig_max_diff = d;
                }
            }
        }
    }
    orig_average = sum / count;
    for (int d : diff) {
        orig_variance += pow(d - orig_average, 2);
    }
    orig_variance /= (count - 1);

    cout << "Initially the average of the difference between capacity and flow of each pipe was: " << orig_average << endl;
    cout << "The variance of the difference between capacity and flow of each pipe was: " << orig_variance << endl;
    cout << "And the maximum difference between capacity and flow of each pipe was: " << orig_max_diff << endl;
    cout << endl;

    // Balancing algorithm
    for (Vertex* v : g.getVertexSet()) {
        if (v->getInfo() != "S" && v->getInfo() != "Si") {
            // Iterate over all edges adjacent to the current vertex
            for (Edge *e: v->getAdj()) {
                int d = e->getCapacity() - e->getFlow();
                e->setFlow(e->getFlow() + d); // Adjust flow to minimize imbalance
            }
        }
    }

    // Calculate final metrics
    diff.clear();
    int final_max_diff = INT_MIN;
    sum = 0, count = 0;
    double final_average = 0, final_variance = 0;
    for (Vertex* v : g.getVertexSet()) {
        // Iterate over all edges adjacent to the current vertex
        for (Edge* e : v->getAdj()) {
            int d = e->getCapacity() - e->getFlow();
            diff.push_back(d);
            sum += d;
            count++;
            if (d > final_max_diff) {
                final_max_diff = d;
            }
        }
    }
    final_average = sum / count;
    for (int d : diff) {
        final_variance += pow(d - final_average, 2);
    }
    final_variance /= (count - 1);

    cout << "After using the balancing algorithm the average of the difference between capacity and flow of each pipe is: " << final_average << endl;
    cout << "The variance of the difference between capacity and flow of each pipe is: " << final_variance << endl;
    cout << "And the maximum difference between capacity and flow of each pipe is: " << final_max_diff << endl;
}

