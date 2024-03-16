#define WATER_SUPPLY_MANAGEMENT_GRAPH_H

#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
    T info;
    vector<Edge<T> > adj;
    bool visited;
    vector<Vertex<T>> prev;
    int indegree;
    int dist;
    void addEdge(Vertex<T> *dest);
    void addEdge(Vertex<T> *dest, T info);
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
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
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
    Edge(Vertex<T> *d, T info);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    int getWeight() const;
    int getFlow() const;
    int getCapacity() const;
    void setWeight();
    void getFlow();
    void getCapacity();
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;
public:
    Graph() = default;
    Graph(T t);
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    T getAirline() const;
    void setAirline(T al);
    bool addEdge(const T &sourc, const T &dest);
    bool addEdge(const T &sourc, const T &dest, const T info);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    void dfsArticulationPoints(Vertex<T> * v, int & i, unordered_set<string> & res, stack<T> & s);
    unordered_set<T> articulationPoints();

};

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d): dest(d){}

template <class T>
Edge<T>::Edge(Vertex<T> *d, T info): dest(d), info_edge(info){}

template <class T>
Graph<T>::Graph(T t) {
    this->airline = t;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
string Vertex<T>::getPrev() const {
    return prev;
}

template<class T>
void Vertex<T>::setPrev(string p){
    Vertex::prev = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
T Edge<T>::getInfoEdge() const {
    return info_edge;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}

template<class T>
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2);
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, const T info) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, info);
    return true;
}

template <class T>
T Graph<T>::getAirline() const {
    return airline;
}

template <class T>
void Graph<T>::setAirline(T al) {
    Graph::airline = al;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d) {
    adj.push_back(Edge<T>(d));
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, T info) {
    adj.push_back(Edge<T>(d, info));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

/****************** Articulation Points ********************/

template <class T>
unordered_set<T> Graph<T>::articulationPoints() {
    unordered_set<T> res;
    stack<T> s;
    int i = 0;
    for (int v = 0; v < vertexSet.size(); v++){
        vertexSet[v]->num = i;
    }
    i++;

    for (int vertex = 0; vertex < vertexSet.size(); vertex++){
        if (vertexSet[vertex]->num == 0){
            dfsArticulationPoints(vertexSet[vertex], i, res, s);
        }
    }

    return res;
}


template <class T>
void Graph<T>::dfsArticulationPoints(Vertex<T> * v, int & i, unordered_set<string> & res, stack<T> & s) {
    v->num = i;
    v->low = i;
    i++;
    int children = 0;
    s.push(v->getInfo());
    for (Edge<T> edge: v->adj) {
        if (edge.dest->num == 0) {
            children++;
            dfsArticulationPoints(edge.dest, i, res, s);
            v->low = min(v->low, edge.dest->low);
            if (v->info != "CDG" && edge.dest->low >= v->num) {
                res.insert(v->info);
            }
        }
        else if (edge.dest->num > 0) {
            v->low = min(v->low, edge.dest->num);
        }
    }
    s.pop();
    if(v->info == "CDG" && children > 1){
        res.insert(v->getInfo());
    }
}

#endif //PROJETO2_GRAPH_H

