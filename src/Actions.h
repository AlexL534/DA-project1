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
    /**
     * @brief Calculates the maximum amount of water that can reach a specific city.
     *
     * @param g Reference to the graph representing the water supply network.
     * @param city The code of the city for which the maximum flow is to be calculated.
     * @return The maximum amount of water that can reach the specified city.
     */
    int maxFlowSpecificCity(Graph& g, string city); //2.1
    /**
     * @brief Calculates the maximum amount of water that can reach each city.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A map containing the maximum amount of water that can reach each city.
     */
    map<string, int> maxFlowAllCities(Graph& g); //2.2
    /**
     * @brief Balances the water supply network and calculates the metrics.
     *
     * @param g Reference to the graph representing the water supply network.
     */
    void balanceAndCalculateMetrics(Graph& g); //2.3
    struct AffectedCity {
        string code; // Código da cidade
        int deficit; // Déficit no fornecimento de água para a cidade
    };
    /**
     * @brief Identifies the cities in need of water supply.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A map containing the cities in need of water supply and their respective deficits.
     */
    void analyseReservoirs(Graph& g); //3.1
    /**
     * @brief Analyzes the pumping stations in the water supply network.
     *
     * @param g Reference to the graph representing the water supply network.
     */
    void analyzePumpingStations(Graph& g); //3.2
    /**
     * @brief Avoids crucial pipelines in the water supply network.
     *
     * @param g Reference to the graph representing the water supply network.
     */
    void crucialPipelines(Graph& g); //3.3
    /**
     * @brief Identifies the cities in need of water supply.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A map containing the cities in need of water supply and their respective deficits.
     */
    void handleBidirectionalPipe(Edge* edge1, Edge* edge2, const string& source,const string& dest, const map<string, int>& originalFlowMap,Actions& a, Graph& g);
    /**
     * @brief Identifies the cities in need of water supply.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A map containing the cities in need of water supply and their respective deficits.
     */
    void handleUnidirectionalPipe(Edge* edge, const string& source, const string& dest,const map<string, int>& originalFlowMap,Actions& a, Graph& g);
    /**
     * @brief Identifies the cities in need of water supply.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A map containing the cities in need of water supply and their respective deficits.
     */
    map<string, int> citiesInNeed(Graph& g);

    Graph heuristic_evaluation(double orig_variance,double orig_average,double orig_max_diff,Graph &g);
    /**
     * @brief Calculates the metrics of the water supply network.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A vector containing the metrics of the water supply network.
     */
    vector<double> calculateMetrics(Graph& g);
};


#endif
