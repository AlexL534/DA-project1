#define WATER_SUPPLY_MANAGEMENT_GRAPH_H
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <limits>
#include <queue>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

template <class T>
class Vertex {
    T info;
    vector<Edge<T> > adj;
    bool visited;
    vector<Vertex<T>> prev;
    int indegree;
    int dist;
    void addEdge(Vertex<T> *dest);
    void addEdge(Vertex<T> *dest, int weight);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex();
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    string getPrev() const;
    void setPrev(string p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    int getIndegree() const;
    void setIndegree(int indegree);
    friend class Graph<T>;
};

template <class T>
class Edge {
    Vertex<T> * dest;
    int weight;
    int flow;
    int capacity;
public:
    Edge(Vertex<T> *d);
    Edge(Vertex<T> *d, int w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    int getWeight() const;
    int getFlow() const;
    int getCapacity() const;
    void setWeight(int w);
    void setFlow(int f);
    void setCapacity(int c);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;
public:
    Graph() = default;
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &source, const T &dest);
    bool addEdge(const T &source, const T &dest, int weight);
    bool removeEdge(const T &source, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    vector<T> dfs(const T &source) const;
    vector<T> bfs(const T &source) const;
    int fordFulkerson(Graph<T>& G, Vertex<T>* s, Vertex<T>* t);
    void initializeFlow(Graph<T>& G);
    vector<Edge<T>*> findAugmentingPath(Graph<T>& G, Vertex<T>* s, Vertex<T>* t);

};


