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

    bool bfs(Vertex* src, Vertex* snk);

    void updateFlow(Vertex* src, Vertex* snk, int flow);

    void edmondsKarp(const std::string &source, const std::string &sink);

    void fordFulkerson(Graph& g, const std::string &source, const std::string &sink);

    vector<Edge*> findAugmentingPath(Graph& g, const string& source, const string& sink);

    Graph buildGraph(vector<Reservoir> reservoirs, vector<Station> stations, vector<Pipe> pipes, vector<City> cities);
};