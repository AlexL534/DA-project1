#include <algorithm>
#include "graph.h"

Vertex::Vertex(const std::string& in, int i, VertexType t): info(in), id(i), type(t) {}

Edge::Edge(Vertex *d): dest(d) {}

Edge::Edge(Vertex *s, Vertex *d, int ca):src(s), dest(d), capacity(ca) {}

VertexType Vertex::getType() const {
    return type;
}

bool Vertex::isType(VertexType t) const {
    return type == t;
}

void Vertex::printType() const {
    switch (type) {
        case VertexType::STATION:
            std::cout << "Station" << std::endl;
            break;
        case VertexType::RESERVOIR:
            std::cout << "Reservoir" << std::endl;
            break;
        case VertexType::CITY:
            std::cout << "City" << std::endl;
            break;
        default:
            std::cout << "Unknown type" << std::endl;
            break;
    }
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

int Vertex::getIndegree() const {
    return indegree;
}

void Vertex::setIndegree(int ind) {
    indegree = ind;
}



std::vector<Edge*> Vertex::getAdj() const {
    return adj;
}

void Vertex::setAdj(vector<Edge*> ad) {
    adj = ad;
}

vector<Edge *> Vertex::getPath() const {
    return path;
}

void Vertex::setPath(vector<Edge *> p) {
    path = p;
}

bool Graph::addVertex(const std::string& in, VertexType t, int id) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in, id, t));
    return true;
}

Edge Graph::findEdge(const std::string& source, const std::string& dest) {
    for (auto e: allEdges[source]){
        if(dest == e.dest->info){
            return e;
        }
    }
    return nullptr;
}

map<string, vector<Edge>> Graph::getAllEdges() {
    return allEdges;
}

bool Graph::addEdge(const std::string& source, const std::string& dest, int direction, int capacity) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    if (direction == 1) {
        v1->addEdge(v1, v2, capacity);
        allEdges[v1->info].push_back(Edge(v1, v2, capacity));
    }
    else if (direction==0) {
        v1->addEdge(v1, v2, capacity);
        allEdges[v1->info].push_back(Edge(v1, v2, capacity));
        v2->addEdge(v2, v1, capacity);
        allEdges[v2->info].push_back(Edge(v2, v1, capacity));
    }
    return true;
}

void Vertex::addEdge(Vertex* src, Vertex* dest, int capacity) {
    Edge* edge = new Edge(src, dest, capacity);
    adj.push_back(edge);
    dest->path.push_back(edge);
}

bool Graph::removeEdge(const std::string& source, const std::string& dest) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdgeTo(v2);
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
                auto it = edge->dest->path.begin();
                while(it != edge->dest->path.end()){
                    it = edge->dest->path.erase(it);
                }
            }
            for (auto u : vertexSet){
                u->removeEdgeTo(v);
            }
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

std::vector<std::string> Graph::dfs(const std::string& source) const {
    std::vector<std::string> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
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

        //cout << endl<< "all flows : " << endl;

        for(auto it:vertexSet){
            for(auto it2:it->adj){
                //cout <<endl<< it2->src->info<< " to " << it2->dest->info << " capacity : " <<it2->capacity<< "flow : " << it2->flow;
            }
        }

        int flow = INT_MAX;
        //cout << endl << "Min residual" << endl;

        for (auto it = snk; it!= src;){
            Edge* edge = it->getPrev();
            if(edge->getDest()->info == it->info){
                //cout << "a";
                it = edge->src;
                //cout <<endl<< "A : " << edge->getCapacity() << ' ' << edge->getFlow();
                flow = std::min(flow, edge->getCapacity() - edge->getFlow());
            }
            else {
                it = edge->getDest();
                //cout <<endl<< "B : " << edge->getCapacity() << ' ' << edge->getFlow();
                flow = std::min(flow, edge->getFlow());
            }
        }



        updateFlow(src, snk, flow);

    }


}

