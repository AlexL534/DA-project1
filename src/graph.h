#define WATER_SUPPLY_MANAGEMENT_GRAPH_H
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
    int indegree;
    int dist;
    void addEdge(Vertex *src, Vertex *dest, int capacity);
    bool removeEdgeTo(Vertex *d);
public:
    Vertex();
    Vertex(const std::string& in, int i, VertexType t);
    std::string getInfo() const;
    void setInfo(const std::string& in);
    int getId() const;
    VertexType getType() const;
    bool isType(VertexType t) const;
    void printType() const;
    bool isVisited() const;
    void setVisited(bool v);
    Edge* getPrev() const;
    void setPrev(Edge* prev);
    vector<Edge*> getPath() const;
    void setPath( vector<Edge *> p);
    vector<Edge*> getAdj() const;
    void setAdj( vector<Edge *> adj);
    int getIndegree() const;
    void setIndegree(int indegree);
    friend class Graph;
};

class Edge {
    Vertex * src;
    Vertex * dest;
    int flow;
    int capacity;
    int weight;
public:
    Edge(Vertex *d);
    Edge(Vertex *s, Vertex *d, int ca);
    Vertex *getDest() const;
    Vertex *getSource() const;
    void setDest(Vertex *dest);
    int getWeight() const;
    int getFlow() const;
    int getCapacity() const;
    void setWeight(int w);
    void setFlow(int f);
    void setCapacity(int c);
    friend class Graph;
    friend class Vertex;
};

class Graph {
    vector<Vertex*> vertexSet;
    map<string, vector<Edge>> allEdges;
public:
    Graph() = default;
    Vertex *findVertex(const std::string &in) const;
    int getNumVertex() const;
    Edge* findEdge(const std::string& source, const std::string& dest);
    bool addVertex(const std::string &in, VertexType t, int id);
    bool removeVertex(const std::string &in);
    bool removePath(Edge * e);
    bool addEdge(const std::string &source, const std::string &dest, int direction, int capacity);
    bool removeEdge(const std::string &source, const std::string &dest);
    vector<Vertex*> getVertexSet() const;
    std::vector<Edge*> getAdjacentEdges(const std::string& vertexInfo) const;
    map<string,vector<Edge>> getEdgesSet() const;
    void dfsVisit(Vertex *v, vector<std::string>& res) const;
    vector<std::string> dfs(const std::string &source) const;
    bool bfs(Vertex* src, Vertex* snk);
    void updateFlow(Vertex* src, Vertex* snk, int flow);
    void edmondsKarp(const std::string &source, const std::string &sink);
    bool addFlow(int flow, Vertex * vertex);
    void fordFulkerson(Graph& g, const std::string &source, const std::string &sink);
    vector<Edge*> findAugmentingPath(Graph& g, const string& source, const string& sink);
    Graph buildGraph(vector<Reservoir> reservoirs, vector<Station> stations, vector<Pipe> pipes, vector<City> cities);
};