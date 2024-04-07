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

map<string, int> Actions::citiesInNeed(Graph &g) {
    map<string, int> m;
    map<string, int> res;
    m = maxFlowAllCities(g);
    for(auto it:cities){
        float value = (float) m[it.getCode()];
        if(it.getDemand() - value > 0) res[it.getCode()] = it.getDemand() - value;
    }
    return res;
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

    //remove these vertices so that graph is not altered
    g.removeVertex("Si");
    g.removeVertex("S");
}


void Actions::analyzePumpingStations(Graph& g) {
    int count = 0; //number of stations that can be removed
    vector<string> canBeRemoved;
    map<string, vector<AffectedCity>> station_city;

    Actions a(reservoirs, stations, cities, pipes);

    //Map that will store the flow in the city before removing the vertex (for comparison later on)
    map<string, int> initialFlowMap = a.maxFlowAllCities(g);

    // Iterate through each pumping station in the network
    for (const auto& station: stations) {
        bool cityWaterSupplyAffected = false;

        // Create a copy of the original graph
        Graph tempGraph = g;

        for (auto& edge : tempGraph.getAdjacentEdges(station.getCode())) {
            edge->setCapacity(0);
            edge->setFlow(0);
        }

        // Map to store the flow in each city after removing the pumping station
        map<string, int> currentFlowMap = a.maxFlowAllCities(tempGraph);

        // Vector to store information about affected cities
        vector<AffectedCity> affectedCities; //will store the codes

        // Iterate through each city in the network
        for (const auto &city: cities) {
            // Check if the city's water supply is affected
            if (currentFlowMap[city.getCode()] < initialFlowMap[city.getCode()]) { //current flow different from the initial
                // Record the affected city and its water supply deficit
                int deficit = city.getDemand() - a.maxFlowSpecificCity(tempGraph, city.getCode());
                affectedCities.push_back({city.getCode(), deficit});
                cityWaterSupplyAffected = true;
            }
        }
        //Insert the affectedCities vector on the map
        station_city.insert({station.getCode(), affectedCities});


        if (!cityWaterSupplyAffected) {
            count++;
            canBeRemoved.push_back(station.getCode());
        }
    }
    if (count == 0) {
        cout << "There are no pumping stations that can be temporarily taken out of service." << endl;
    } else {
        cout << "There are " << count << " pumping stations that can be temporarily taken out of service: ";
        for (auto s: canBeRemoved) {cout<<s;}
        cout << endl;
    }

    int choice;
    cout << "Do you wish to see the cities affected by the removal of a certain pumping station?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        do {
            string stationCode;
            cout << "Enter the code of the pumping station: ";
            cin >> stationCode;

            // Display affected cities for the specified pumping station
            if (station_city.find(stationCode) != station_city.end()) {
                cout << "Pumping station " << stationCode << " affects the following cities:" << endl;
                for (const auto &city: station_city[stationCode]) {
                    cout << "City " << city.code << " has a water supply deficit of " << city.deficit << endl;
                }
            } else {
                cout << "Invalid pumping station code." << endl;
            }

            // Ask the user if they want to check another pumping station
            cout << "Do you want to check another pumping station?\n";
            cout << "1. Yes\n";
            cout << "2. No\n";
            char answer;
            cin >> answer;
            if (answer == '2') break;
        } while(true);
    }
}

void Actions::crucialPipelines(Graph& g) {
    Actions a(reservoirs, stations, cities, pipes);
    map<string, int> originalFlowMap = a.maxFlowAllCities(g);

    for (const auto& pipe : pipes) {
        string source = pipe.getPointA();
        string dest = pipe.getPointB();
        int direction = pipe.getDirection();

        Edge* edge = nullptr;
        Edge* edge2 = nullptr; // For bidirectional pipes

        if (direction == 1) {
            edge = g.findEdge(source, dest);
        } else { // Bidirectional
            edge = g.findEdge(source, dest);
            edge2 = g.findEdge(dest, source);
        }

        if (edge == nullptr) {
            // Handle edge not found
            continue;
        }

        // Handle unidirectional pipes
        if (direction == 1) {
            handleUnidirectionalPipe(edge, source, dest, originalFlowMap, a, g);
        } else { // Handle bidirectional pipes
            handleBidirectionalPipe(edge, edge2, source, dest, originalFlowMap, a, g);
        }
    }
}

void Actions::handleUnidirectionalPipe(Edge* edge, const string& source, const string& dest,
                                       const map<string, int>& originalFlowMap,
                                       Actions& a, Graph& g) {

    int originalCapacity = edge->getCapacity();
    int originalFlow = edge->getFlow();
    edge->setCapacity(0);
    edge->setFlow(0);

    map<string, int> currentFlowMap = a.maxFlowAllCities(g);

    edge->setCapacity(originalCapacity);
    edge->setFlow(originalFlow);

    map<string,float> deficits;
    for (const auto &city: cities) {
        auto it = originalFlowMap.find(city.getCode());
        if (it != originalFlowMap.end()) {
            int initialFlow = it->second;
            int currentFlow = currentFlowMap[city.getCode()];
            float cityDemand = city.getDemand();
            if (currentFlow < initialFlow) {
                deficits[city.getCode()] = cityDemand - currentFlow;
            }
        }
    }

    if (!deficits.empty()) {
        cout << source << " - " << dest << " is removed. Cities affected:" << endl;
        for (const auto& pair : deficits) {
            cout << "City " << pair.first << " has a water supply deficit of " << pair.second << endl;
        }
        cout << endl;
    } else {
        cout << source << " - " << dest << " is removed. No city is affected." << endl;
    }
}


void Actions::handleBidirectionalPipe(Edge* edge1, Edge* edge2, const string& source, const string& dest,
                                      const map<string, int>& originalFlowMap,
                                      Actions& a, Graph& g) {
    int originalCapacity1 = edge1->getCapacity();
    int originalFlow1 = edge1->getFlow();
    edge1->setCapacity(0);
    edge1->setFlow(0);

    int originalFlow2 = edge2->getFlow();
    edge2->setCapacity(0);
    edge2->setFlow(0);

    map<string, int> currentFlowMap = a.maxFlowAllCities(g);

    edge1->setCapacity(originalCapacity1);
    edge1->setFlow(originalFlow1);
    edge2->setCapacity(originalCapacity1);
    edge2->setFlow(originalFlow2);

    map<string,int> deficits;
    for (const auto &city: cities) {
        auto it = originalFlowMap.find(city.getCode());
        if (it != originalFlowMap.end()) {
            int initialFlow = it->second;
            int currentFlow = currentFlowMap[city.getCode()];
            if (currentFlow < initialFlow) {
                deficits[city.getCode()] = initialFlow - currentFlow;
            }
        }
    }

    if (!deficits.empty()) {
        cout << source << " - " << dest << " is removed. Cities affected:" << endl;
        for (const auto& pair : deficits) {
            cout << "City " << pair.first << " has a water supply deficit of " << pair.second << endl;
        }
        cout << endl;
    } else {
        cout << source << " - " << dest << " is removed. No city is affected." << endl;
        cout << "\n";
    }
}