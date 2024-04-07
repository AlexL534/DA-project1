#include <algorithm>
#include "graph.h"

Vertex::Vertex(const std::string& in, int i, VertexType t): info(in), id(i), type(t) {}

Edge::Edge(Vertex *d): dest(d) {}

Edge::Edge(Vertex *s, Vertex *d, int ca):src(s), dest(d), capacity(ca) {}

bool Vertex::isType(VertexType t) const {
    return type == t;
}

int Vertex::getId() const {
    return id;
}

std::string Vertex::getInfo() const {
    return info;
}

void Vertex::setInfo(const std::string& in) {
    info = in;
}

Edge* Vertex::getPrev() const {
    return prev;
}

void Vertex::setPrev(Edge* p) {
    prev = p;
}

Vertex* Edge::getDest() const {
    return dest;
}

Vertex* Edge::getSource() const {
    return src;
}

void Edge::setDest(Vertex* d) {
    dest = d;
}

int Edge::getCapacity() const {
    return capacity;
}

void Edge::setFlow(int f) {
    flow = f;
}

int Edge::getFlow() const {
    return flow;
}

void Edge::setCapacity(int c) {
    capacity = c;
}

Vertex* Graph::findVertex(const std::string& in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return nullptr;
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

std::vector<Edge*> Graph::getAdjacentEdges(const std::string& vertexInfo) const {
    std::vector<Edge*> adjacentEdges;
    for (auto v : vertexSet) {
        if (v->getInfo() == vertexInfo) {
            adjacentEdges = v->getAdj();
            break;
        }
    }
    return adjacentEdges;
}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool v) {
    visited = v;
}

std::vector<Edge*> Vertex::getAdj() const {
    return adj;
}

vector<Edge *> Vertex::getPath() const {
    return path;
}

bool Graph::addVertex(const std::string& in, VertexType t, int id) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in, id, t));
    return true;
}

Edge* Graph::findEdge(const std::string& source, const std::string& dest) {
    // Iterate over all vertices
    for (auto& vertex : vertexSet) {
        // Iterate over adjacent edges of each vertex
        for (auto& edge : vertex->getAdj()) {
            // Check if the edge connects source and dest vertices
            if (vertex->getInfo() == source && edge->getDest()->getInfo() == dest) {
                return edge;
            }
                // If the edge is bidirectional, check the reverse direction
            else if (vertex->getInfo() == dest && edge->getDest()->getInfo() == source) {
                return edge;
            }
        }
    }
    // Edge not found
    return nullptr;
}


bool Graph::addEdge(const std::string& source, const std::string& dest, int direction, int capacity) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    if (direction == 1) {
        v1->addEdge(v1, v2, capacity);
    }
    else if (direction==0) {
        v1->addEdge(v1, v2, capacity);
        v2->addEdge(v2, v1, capacity);
    }
    return true;
}

void Vertex::addEdge(Vertex* src, Vertex* dest, int capacity) {
    Edge* edge = new Edge(src, dest, capacity);
    adj.push_back(edge);
    dest->path.push_back(edge);
}

bool Vertex::removeEdgeTo(Vertex* d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if ((*it)->dest == d) {
            adj.erase(it);
            return true;
        }
    return false;
}



bool Graph::removeVertex(const std::string& in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++){
        //cout << "ccc";
        if ((*it)->info == in) {
            //cout << "ddd";
            Vertex * v = *it;
            auto e = v->adj.begin();
            while(e != v->adj.end()){
                Edge *edge = *e;
                e = v->adj.erase(e);
                auto it2 = edge->dest->path.begin();
                while(it2 != edge->dest->path.end()){
                    it2 = edge->dest->path.erase(it2);
                }
            }
            for (auto u : vertexSet){
                u->removeEdgeTo(v);
            }
            vertexSet.erase(it);
            return true;
        }
    }
    return false;
}

void Graph::dfsVisit(Vertex* v, std::vector<std::string>& res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto& e : v->adj) {
        auto w = e->dest;
        if (!w->visited)
            dfsVisit(w, res);
    }
}

bool Graph::bfs(Vertex* src, Vertex* snk) {
    queue<Vertex *> q;

    for (auto it : this->getVertexSet()){
        it->setVisited(false);
    }

    src->setVisited(true);
    q.push(src);

    while (!q.empty() && !snk->isVisited()){
        Vertex* u = q.front();
        q.pop();
        for (auto edge: u->getAdj()){
            //cout << endl << "Residual : " << edge->getDest()->info<< ' ' << edge->capacity - edge->flow << endl;
            if (edge->capacity - edge->flow > 0 && !edge->getDest()->isVisited()){
                Vertex* v = edge->getDest();
                v->setVisited(true);
                v->setPrev(edge);
                q.push(v);
            }
        }

        for(auto edge: u->getPath()){
            //cout << endl << "Residual : " << edge->src->info<< ' ' << edge->capacity - edge->flow << endl;
            Vertex* v = edge->src;
            if(edge->flow > 0 && !v->isVisited()){
                v->setVisited(true);
                v->setPrev(edge);
                q.push(v);

            }
        }
    }
    return snk->isVisited();
}

Graph Graph::buildGraph(vector<Reservoir> reservoirs, vector<Station> stations, vector<Pipe> pipes, vector<City> cities){
    Graph g;
    for (auto r:reservoirs){
        g.addVertex(r.getCode(), VertexType::RESERVOIR, r.getId());
    }

    for(auto s: stations){
        g.addVertex(s.getCode(), VertexType::STATION, s.getId());
    }

    for(auto c: cities){
        g.addVertex(c.getCode(), VertexType::CITY, c.getId());
    }

    for(auto p: pipes){
        g.addEdge(p.getPointA(), p.getPointB(), p.getDirection(), p.getCapacity());
    }

    return g;
}

void Graph::updateFlow(Vertex *src, Vertex *snk, int flow) {
    //cout << endl << "Flow : " << flow << endl;
    for (auto v = snk; v != src;) {
        auto e = v->getPrev();
        int f = e->getFlow();
        //cout <<"f : " << f << ' ';
        if (e->getDest()->info == v->info) {
            e->setFlow(f + flow);
            v = e->src;
        }
        else {
            e->setFlow(f - flow);
            v = e->getDest();
        }
    }
}

void Graph::edmondsKarp(const std::string &source, const std::string &sink) {
    for (auto it : this->getVertexSet()){
        for (auto it2 : it->getAdj()){
            it2->setFlow(0);
        }
    }
    Vertex* src = findVertex(source);
    Vertex* snk = findVertex(sink);

    while(bfs(src, snk)){

        int flow = INT_MAX;

        for (auto it = snk; it!= src;){
            Edge* edge = it->getPrev();
            if(edge->getDest()->info == it->info){
                it = edge->src;
                flow = std::min(flow, edge->getCapacity() - edge->getFlow());
            }
            else {
                it = edge->getDest();
                flow = std::min(flow, edge->getFlow());
            }
        }
        updateFlow(src, snk, flow);
    }
}

void Graph::fordFulkerson(Graph &g, const std::string &source, const std::string &sink) {
    for (Vertex* v : g.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            e->setFlow(0);
        }
    }

    int maxFlow = 0;

    // Repeat until no augmenting path exists
    while (true) {
        // Find an augmenting path using BFS
        vector<Edge*> path = findAugmentingPath(g, source, sink);
        if (path.empty()) {
            break; // No augmenting path found, terminate
        }

        // Determine the maximum flow that can be pushed through this path
        int minCapacity = std::numeric_limits<int>::max();
        for (Edge* edge : path) {
            minCapacity = std::min(minCapacity, edge->getCapacity() - edge->getFlow());
        }

        // Augment flow along the path
        for (Edge* edge : path) {
            edge->setFlow(edge->getFlow() + minCapacity);
        }

        // Update the maximum flow
        maxFlow += minCapacity;
    }

}

vector<Edge *> Graph::findAugmentingPath(Graph &g, const std::string &source, const std::string &sink) {
    vector<Edge*> path;
    map<Vertex*, Edge*> parent; // Map to store parent edges for each vertex
    queue<Vertex*> q;
    q.push(g.findVertex(source));

    // BFS to find augmenting path
    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();

        // Check if the sink is reached
        if (current->getInfo() == sink) {
            // Reconstruct the augmenting path
            Vertex* v = current;
            while (v != g.findVertex(source)) {
                Edge* edge = parent[v];
                path.push_back(edge);
                v = edge->getSource();
            }
            std::reverse(path.begin(), path.end());
            break;
        }

        // Explore neighbors
        for (Edge* edge : current->getAdj()) {
            Vertex* neighbor = edge->getDest();
            // Check if the neighbor has not been visited and there is residual capacity
            if (!parent.count(neighbor) && edge->getCapacity() > edge->getFlow()) {
                parent[neighbor] = edge;
                q.push(neighbor);
            }
        }
    }

    return path;
}

bool Graph::addFlow(int f, Vertex *vertex) {
    if(!vertex->isType(VertexType::CITY)){return true;}
        vertex->setVisited(true);
        for(auto edge: vertex->getAdj()){
            if(!edge->getDest()->isVisited()){
                int capacity = (int) edge->getCapacity();
                int flow = (int) edge->getFlow();
                int remaining = capacity - flow;
                int adjacentFlow = 0;
                for(auto it1: vertex->getAdj()){adjacentFlow += it1->getFlow();}
                cout << "a";
                if (adjacentFlow >= f && remaining >= f){
                    cout << "b";
                    int ff = min(f, remaining);
                    edge->setFlow(flow + ff);

                    Vertex * newVertex = edge->getDest();
                    if(addFlow(ff, newVertex)){
                        cout << "c";
                        return true;
                    }
                    cout << "d";
                    edge->setFlow(flow - ff);

                }

            }
        }

    return false;
}
