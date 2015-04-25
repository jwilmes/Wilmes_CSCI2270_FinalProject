/*Created by Justin Wilmes
    April, 2015
*/

#ifndef GRAFF_H_INCLUDED
#define GRAFF_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <queue>
#include <inttypes.h>
#include <limits.h>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::queue;

struct vertex;

struct Hnode{
    string name;
    int weight;
    Hnode * next;
    vertex * v;
};

struct adjVertex{
    vertex * v;
    int weight;
};

struct queueVertex{
    int distance; //# edges on path
    std::vector<vertex> path; //vertices on path
};

struct vertex{
    string name;
    bool visited;
    int distance;
    vertex * previous;
    int district;
    vector<adjVertex> adj;
};

class Graff{
public:
    Graff();
    ~Graff();
    //Standard graph-type functions (modified to increase functionality):
        void addEdge(string v1, string v2, int weight);
        void addVertex(string name);
        void findDistricts();
        void displayEdges();
        void BFTraversal(string city);
        void Dijkstra(string starting, string destination);
        void displayVertices();
        queueVertex * BFSearch(string city, string destination);
    //new graph-type functions
        queueVertex * DFSearch(string start, string destination);
        void delV(string name);
        void modAdjdel(string name,string s);
protected:
private:
    vector<vertex> vertices;
    int runT;
    int versize;
    int hashSum(string s, int i);
    void BFS(vertex v,int i);
    void visSet();
    vertex * Vfinder(string s, vertex * v);
    void rtimprint();
    void rsltprint(vertex * v);
};


#endif // GRAFF_H_INCLUDED
