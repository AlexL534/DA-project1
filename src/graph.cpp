#include "graph.h"

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d): dest(d){}

template <class T>
Edge<T>::Edge(Vertex<T> *d, int w): dest(d), weight(w){}


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
int Edge<T>::getWeight() const {
    return weight;
}

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

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &source, const T &dest) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2);
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &source, const T &dest, int weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, weight);
    return true;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d) {
    adj.push_back(Edge<T>(d));
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, int weight) {
    adj.push_back(Edge<T>(dest, weight));
}

template <class T>
bool Graph<T>::removeEdge(const T &source, const T &dest) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

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


template <class T>
vector<T> Graph<T>::dfs(const T& source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}

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

template <class T>
int Graph<T>::fordFulkerson(Graph<T>& G, Vertex<T>* s, Vertex<T>* t) {
    int maxFlow = 0;
    initializeFlow(G);
    while (true) {
        vector<Edge<T>*> path = findAugmentingPath(G, s, t);
        if (path.empty()) break;

        T bottleneckCapacity = std::numeric_limits<T>::max();
        for (auto edge : path) {
            if (edge->getCapacity() < bottleneckCapacity) {
                bottleneckCapacity = edge->getCapacity();
            }
        }

        for (auto edge : path) {
            edge->setFlow(edge->getFlow() + bottleneckCapacity);
        }

        maxFlow += bottleneckCapacity;
    }

    return maxFlow;
}

template <class T>
void Graph<T>::initializeFlow(Graph<T>& G) {
    for (auto vertex : G.getVertexSet()) {
        for (auto& edge : vertex->getAdj()) {
            edge.setFlow(0);
        }
    }
}

template <class T>
vector<Edge<T>*> Graph<T>::findAugmentingPath(Graph<T>& G, Vertex<T>* s, Vertex<T>* t) {
    vector<Edge<T>*> path;
    unordered_map<Vertex<T>*, Edge<T>*> parent;
    queue<Vertex<T>*> q;
    q.push(s);
    parent[s] = nullptr;

    while (!q.empty()) {
        Vertex<T>* current = q.front();
        q.pop();

        if (current == t) {
            while (parent[current] != nullptr) {
                path.push_back(parent[current]);
                current = parent[current]->getSrc();
            }
            reverse(path.begin(), path.end());
            break;
        }

        for (auto& edge : current->getAdj()) {
            Vertex<T>* next = edge.getDest();
            if (edge.getResidualCapacity() > 0 && parent.find(next) == parent.end()) {
                q.push(next);
                parent[next] = &edge;
            }
        }
    }

    return path;
}

