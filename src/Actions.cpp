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

        // Temporarily remove the current pumping station from the network
        tempGraph.removeVertex(station.getCode());

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
        affectedCities.clear();
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

/* Explicação da função
 the function stores the number of stations that can be removed
 inicializamos um mapa em que a chave é o código da station e o valor é um vetor com as cidades afetadas
 it initializes a map, initialFlowMap with the flow of each city before removal
 vai iterar as stations
    sempre que iterar vai criar um tempGraph que é uma cópia do inicial, e remover uma station
    inicializamos outro mapa com o flow de cada cidade para o grafo sem uma station
    é criado um vetor onde serão armazendas as cidades afetadas
    iteramos por todas as cidades
        se o flow tiver sido afetado
            colocamos o código da cidade e o défice no vetor
    metemos a station e o vetor no map
 */

//THIS IS CODE THAT I HAD BEEN USING, MAY BE HELPFUL. DELETE BEFORE SUBMISSION
/*
    // Display the analysis results
    for (const auto &entry: station_city) {
        const string &stationCode = entry.first;
        const vector<AffectedCity> &affectedCities = entry.second;

        if (!affectedCities.empty()) {
            cout << "Pumping station " << stationCode << " affects the following cities:" << endl;
            for (const auto &city: affectedCities) {
                cout << "City " << city.code << " has a water supply deficit of " << city.deficit << endl;
            }
        } else {
            cout << "Pumping station " << stationCode
                 << " can be temporarily removed without affecting any city's water supply." << endl;
        }
    }
     */


void Actions::crucialPipelines(Graph& g) {
    map<string, vector<AffectedCity>> pipe_city;
    Actions a(reservoirs, stations, cities, pipes);
    //Map that will store the flow in the city before removing the vertex (for comparison later on)
    map<string, int> initialFlowMap = a.maxFlowAllCities(g);
    for (auto& pipe: pipes) {
        // Generate pipe code using service points and capacity
        string pipeCode = pipe.getPointA() + "_" + pipe.getPointB() + "_" + to_string(pipe.getCapacity());
        int capacity = pipe.getCapacity();
        pipe.setCapacity(0);

        map<string, int> currentFlowMap = a.maxFlowAllCities(g);
        vector<AffectedCity> affectedCities;
        for (const auto &city: cities) {
            // Check if the city's water supply is affected
            if (currentFlowMap[city.getCode()] < initialFlowMap[city.getCode()]) { //current flow different from the initial
                // Record the affected city and its water supply deficit
                int deficit = initialFlowMap.at(city.getCode()) - a.maxFlowSpecificCity(g, city.getCode());
                affectedCities.push_back({city.getCode(), deficit});
            }
        }
        pipe_city.insert({pipeCode, affectedCities});
        affectedCities.clear();
        pipe.setCapacity(capacity);
    }
}

/*
 preciso de um mapa em que a chave vai ser o código da pipe e o valor um vetor das cidades afetadas
 iterar as pipes
 fazer pipe->setCapacity = 0
 ver as cidades afetadas, calcular o seu défice
 */