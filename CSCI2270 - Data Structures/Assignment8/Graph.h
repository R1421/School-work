#include <iostream>
#include <vector>

#ifndef GRAPH.H
struct vertex;

struct adjVertex
{
    vertex *v;
    int weight;
};

struct vertex
{
    std::string name;
    int distance;
    vertex *previous;
    bool visited;
    std::vector<adjVertex> adj;
    int ID;
};

class Graph
{
private:
    std::vector<vertex> vertices;
protected:
public:
    Graph(std::string);
    ~Graph();
    void addEdge(std::string, std::string, int);
    void addVertex(std::string);
    void displayGraph();
    void findDistricts();
    void Dijkstra(std::string, std::string);
    void shortestPath(std::string, std::string);
};
#endif // GRAPH
