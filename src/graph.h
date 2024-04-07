#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <limits>
#include <queue>
#include <map>
#include "Reservoir.h"
#include "City.h"
#include "Pipe.h"
#include "Station.h"

using namespace std;

class Edge;
class Graph;
class Vertex;

enum class VertexType {
    STATION,
    RESERVOIR,
    CITY
};

class Vertex {
    int id;
    VertexType type;
    std::string info;
    vector<Edge *> adj;
    vector<Edge *> path;
    bool visited;
    Edge* prev;
    /**
     * @brief Add an edge to the vertex
     *
     * @param src
     * @param dest
     * @param capacity
     */
    void addEdge(Vertex *src, Vertex *dest, int capacity);
    /**
     * @brief Remove an edge from the vertex
     *
     * @param d
     * @return true
     * @return false
     */
    bool removeEdgeTo(Vertex *d);
public:
    Vertex();
    /**
     * @brief Construct a new Vertex object
     *
     * @param in
     * @param i
     * @param t
     */
    Vertex(const std::string& in, int i, VertexType t);
    std::string getInfo() const;
    void setInfo(const std::string& in);
    /**
     * @brief Get the Id object
     *
     * @return int
     */
    int getId() const;
    VertexType getType() const;
    /**
     * @brief Check if the vertex is of a certain type
     *
     * @param t
     * @return true
     * @return false
     */
    bool isType(VertexType t) const;
    void printType() const;
    /**
     * @brief Get the Adj object
     *
     * @return vector<Edge*>
     */
    bool isVisited() const;
    /**
     * @brief Set the Visited object
     *
     * @param v
     */
    void setVisited(bool v);
    Edge* getPrev() const;
    void setPrev(Edge* prev);
    vector<Edge*> getPath() const;
    void setPath( vector<Edge *> p);
    vector<Edge*> getAdj() const;
    void setAdj( vector<Edge *> adj);
    friend class Graph;
};

class Edge {
    Vertex * src;
    Vertex * dest;
    int flow;
    int capacity;
public:
    Edge(Vertex *d);
    Edge(Vertex *s, Vertex *d, int ca);
    Vertex *getDest() const;
    Vertex *getSource() const;
    void setDest(Vertex *dest);
    int getFlow() const;
    int getCapacity() const;
    void setFlow(int f);
    void setCapacity(int c);
    friend class Graph;
    friend class Vertex;
};

class Graph {
    vector<Vertex*> vertexSet;
    map<string, vector<Edge>> allEdges;
public:
    /**
     * @brief Construct a new Graph object
     *
     */
    Graph() = default;

    Vertex *findVertex(const std::string &in) const;

    int getNumVertex() const;

    Edge* findEdge(const std::string& source, const std::string& dest);

    /**
     * @brief Add a vertex to the graph
     *
     * @param in
     * @param t
     * @param id
     * @return true
     * @return false
     */
    bool addVertex(const std::string &in, VertexType t, int id);
    /**
     * @brief Remove a vertex from the graph
     *
     * @param in
     * @return true
     * @return false
     */
    bool removeVertex(const std::string &in);

    bool removePath(Edge * e);
    /**
     * @brief Add an edge to the graph
     *
     * @param source
     * @param dest
     * @param direction
     * @param capacity
     * @return true
     * @return false
     */
    bool addEdge(const std::string &source, const std::string &dest, int direction, int capacity);

    bool removeEdge(const std::string &source, const std::string &dest);
    /**
     * @brief Get the Vertex Set object
     *
     * @return vector<Vertex*>
     */
    vector<Vertex*> getVertexSet() const;
    /**
     * @brief Get the Adjacent Edges object
     *
     * @param vertexInfo
     * @return vector<Edge*>
     */
    std::vector<Edge*> getAdjacentEdges(const std::string& vertexInfo) const;
    map<string,vector<Edge>> getEdgesSet() const;
    void dfsVisit(Vertex *v, vector<std::string>& res) const;
    vector<std::string> dfs(const std::string &source) const;

    /**
     * @brief Perform a breadth-first search (BFS) traversal from a source vertex to a sink vertex.
     *
     * @param src Pointer to the source vertex.
     * @param snk Pointer to the sink vertex.
     * @return true If there is a path from the source to the sink vertex.
     * @return false If there is no path from the source to the sink vertex.
     */
    bool bfs(Vertex* src, Vertex* snk);

    /**
     * @brief Update the flow along the augmenting path in the graph.
     *
     * This function updates the flow along the augmenting path from the source vertex to the
     * sink vertex in the graph after a flow augmentation operation. It adjusts the flow values
     * of edges in the path according to the amount of flow augmentation.
     *
     * @param src Pointer to the source vertex of the augmenting path.
     * @param snk Pointer to the sink vertex of the augmenting path.
     * @param flow The amount of flow augmentation to be added to the edges in the path.
     */
    void updateFlow(Vertex* src, Vertex* snk, int flow);

    /**
     * @brief Implement the Edmonds-Karp algorithm to find the maximum flow in the graph.
     *
     * This function implements the Edmonds-Karp algorithm to find the maximum flow from
     * the source vertex to the sink vertex in the graph. It updates the flow in the graph
     * to achieve the maximum flow.
     *
     * @param source The info attribute of the source vertex.
     * @param sink The info attribute of the sink vertex.
     */
    void edmondsKarp(const std::string &source, const std::string &sink);

    /**
     * @brief Implement the Ford-Fulkerson algorithm to find the maximum flow in the graph.
     *
     * This function applies the Ford-Fulkerson algorithm to find the maximum flow from the
     * source vertex to the sink vertex in the given graph. It initializes the flow on all
     * edges to zero, then iteratively finds augmenting paths using BFS and updates the flow
     * along these paths until no augmenting path exists. It returns the maximum flow value
     * found.
     *
     * @param g Reference to the graph on which the algorithm is applied.
     * @param source The info attribute of the source vertex.
     * @param sink The info attribute of the sink vertex.
     */
    void fordFulkerson(Graph& g, const std::string &source, const std::string &sink);


    /**
     * @brief Find an augmenting path in the graph using the given source and sink vertices.
     *
     * This function finds an augmenting path in the graph from the source vertex to the
     * sink vertex using the given source and sink information. It returns a vector containing
     * pointers to the edges in the augmenting path.
     *
     * @param g Reference to the graph.
     * @param source The info attribute of the source vertex.
     * @param sink The info attribute of the sink vertex.
     * @return vector<Edge*> Vector of pointers to the edges in the augmenting path.
     */
    vector<Edge*> findAugmentingPath(Graph& g, const string& source, const string& sink);

    /**
     * @brief Build a graph from the given data of reservoirs, stations, pipes, and cities.
     *
     * This function constructs a graph based on the provided data of reservoirs, stations,
     * pipes, and cities. It creates vertices and edges accordingly, representing the entities
     * in the water distribution network.
     *
     * @param reservoirs Vector containing data of reservoirs.
     * @param stations Vector containing data of stations.
     * @param pipes Vector containing data of pipes.
     * @param cities Vector containing data of cities.
     * @return Graph Constructed graph representing the water distribution network.
     */
    Graph buildGraph(vector<Reservoir> reservoirs, vector<Station> stations, vector<Pipe> pipes, vector<City> cities);

};