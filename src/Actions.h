#ifndef WATER_SUPPLY_MANAGEMENT_ACTIONS_H
#define WATER_SUPPLY_MANAGEMENT_ACTIONS_H


#include <map>
#include <set>
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
    struct AffectedCity {
        string code; // Código da cidade
        int deficit; // Déficit no fornecimento de água para a cidade
    };
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
    map<string, int> maxFlowAllCities(Graph& g); //2.1
    /**
     * @brief Determine the cities in need of additional water supply.
     *
     * This function calculates the demand for water supply in each city based on the maximum
     * flow computed for the water distribution network represented by the given graph. It
     * compares the demand for water in each city with the maximum flow reaching that city and
     * identifies the cities where the supply doesn't meet the demand. The result is a map
     * containing the names of cities and the deficit amount of water they require.
     *
     * @param g Reference to the graph representing the water distribution network.
     * @return std::map<std::string, int> A map containing the names of cities in need and their
     * deficit amount of water supply.
     */
    map<string, int> citiesInNeed(Graph& g); //2.2
    /**
     * @brief Balances the water supply network and calculates the metrics.
     *
     * @param g Reference to the graph representing the water supply network.
     */
    void balanceAndCalculateMetrics(Graph& g); //2.3
    /**
     * @brief Perform heuristic evaluation to optimize water flow in the graph.
     *
     * This function conducts a heuristic evaluation of the water distribution network
     * represented by the given graph to optimize water flow. It calculates the maximum flow
     * for all cities in the network and adjusts the flow through edges based on predefined
     * heuristic rules. The objective is to ensure that each city's demand is met efficiently
     * while considering the capacities of pipes and reservoirs. The function returns the modified
     * graph after applying the heuristic evaluation.
     *
     * @param g Reference to the graph representing the water distribution network.
     * @return Graph The modified graph after heuristic evaluation.
     */
    Graph heuristic_evaluation(Graph &g); //2.3
    /**
     * @brief Calculates the metrics of the water supply network.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A vector containing the metrics of the water supply network.
     */
    vector<double> calculateMetrics(Graph& g);//2.3
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
     * @brief Identifies the cities in need of water supply.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A map containing the cities in need of water supply and their respective deficits.
     */
    void handleBidirectionalPipe(Edge* edge1, Edge* edge2, const string& source,const string& dest, const map<string, int>& originalFlowMap,Actions& a, Graph& g, std::map<std::string, float>& affectedCities);
    /**
     * @brief Identifies the cities in need of water supply.
     *
     * @param g Reference to the graph representing the water supply network.
     * @return A map containing the cities in need of water supply and their respective deficits.
     */
    void handleUnidirectionalPipe(Edge* edge, const string& source, const string& dest,const map<string, int>& originalFlowMap,Actions& a, Graph& g, std::map<std::string, float>& affectedCities);
    /**
     * @brief Identify crucial pipelines and their impact on affected cities.
     *
     * This function analyzes the water distribution network represented by the given graph
     * to identify crucial pipelines between the specified source and destination vertices.
     * It determines the impact of these pipelines on affected cities, considering the current
     * flow distribution in the network. The result is a nested map structure containing
     * information about the crucial pipelines and their impact on affected cities.
     *
     * @param g Reference to the graph representing the water distribution network.
     * @param sourceVertex The info attribute of the source vertex of crucial pipelines.
     * @param destVertex The info attribute of the destination vertex of crucial pipelines.
     * @return std::map<std::string, std::map<std::string, std::map<std::string, float>>> A map containing
     * information about crucial pipelines and their impact on affected cities.
     */
    std::map<std::string, std::map<std::string, std::map<std::string, float>>> crucialPipelines(Graph& g, const std::string& sourceVertex, const std::string& destVertex); //3.3
    /**
     * @brief Identify crucial pipelines affecting a specific city and their impact on water supply.
     *
     * This function analyzes the water distribution network represented by the given graph
     * to identify crucial pipelines connected to the specified city. It simulates pipeline
     * malfunctions by temporarily setting their capacities to zero and recalculates the flow
     * distribution in the network. If any city experiences a water supply deficit due to the
     * malfunctioning pipelines, those pipelines are deemed crucial for the specified city.
     *
     * @param g Reference to the graph representing the water distribution network.
     * @param cityCode The unique code identifying the city.
     */
    void crucialPipelines(Graph& g, const std::string& cityCode); //3.3
};
#endif