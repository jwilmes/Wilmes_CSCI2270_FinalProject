/*Created by Justin Wilmes
    April, 2015
*/

#include "Graff.h"
//#include "HasTble.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::queue;

Graff::Graff(){
//builds the "graff" (graph) that is to be used.
    runT=0;
    versize = 0;
}


Graff::~Graff(){
//Deletes the "graff"
    vertices.clear();
}


void Graff::addEdge(string v1, string v2, int weight){
    /*Adds edges (connections) for nodes already existing on the graph*/
    runT=0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){ //make sure start and end are both found before writing edge
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;          runT++; //make adjVertex
                    av.v = &vertices[j];  runT++;  //set its pointer
                    av.weight = weight;   runT++;  //set weight
                    vertices[i].adj.push_back(av); runT++;
                    //another vertex for edge in other direction (ensure symmetry for bidirectional edges)
                    /*adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
}


void Graff::addVertex(string n){
    /*Inserts nodes into the graph (Graff), insuring that identical nodes don't exist*/
    runT=0;
    bool found = false; runT++;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true; runT++;
            cout<<vertices[i].name<<" found.  Please enter a different name/item."<<endl;
        }
    }
    if(found == false){
        vertex v; runT++;
        v.district = -1; runT++;
        v.name = n; runT++;
        v.visited = false;runT++;
        vertices.push_back(v);runT++;
    }
}


void Graff::displayEdges(){
    /*loops through all vertices and adjacent vertices
    and displays the connections of each
    */
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){ //for each element in vertices
            cout<<vertices[i].adj[j].v->name<<"***";
        }
        cout<<endl;
    }
}


void Graff::displayVertices(){
    /*Displays all vertices and connections in the Graff
    Created: April, 2015
    by Justin Wilmes*/
    //loop through vertices:
    int i;
    for(i = 0; i < vertices.size();i++){
        cout<< vertices[i].district <<":"<<vertices[i].name<<"-->";
        for(int j = 0;j<vertices[i].adj.size();j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1){
                cout<<"***";
            }
        }
        cout<<endl;
    }
    cout<<"Number of elements: "<<i<<endl;
    return;
}


void Graff::BFTraversal(string startingCity){
/*A breadth-first traversal through the graph to determine connections
    Created: April, 2015
*/
//Pseudocode:
    /*let Q be a queue
     Q.enqueue(v)
     label v as discovered
     while Q is not empty
        v <- Q.dequeue()
        for all edges from v to w in G.adjacentEdges(v) do
            if w is not labeled as discovered
                Q.enqueue(w)
                label w as discovered*/
    runT=0;
    queue <vertex> Q; runT++;
    int i = 0;  runT++;
    vertex v;  runT++;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].visited = false;  runT++;
    }
    for(int j = 0; j < vertices.size(); j++){
        if(vertices[j].name == startingCity){
            v = vertices[j];  runT++;
            v.visited = true;  runT++;
        }
    }
    Q.push(v);   runT++;
    v.visited = true;  runT++;
    cout<<v.name<<endl;
    vertex u;  runT++;
    while(!Q.empty()){
        u = Q.front();  runT++;
        Q.pop();
        if(u.name!=v.name)
            cout<<u.name<<endl;
        for(i=0; i<u.adj.size(); i++){
            if(u.adj[i].v->visited == false){
                u.adj[i].v->visited = true;  runT++;
                vertex * t = u.adj[i].v;  runT++;
                Q.push(*t);  runT++;
            }
        }
    }
    rtimprint();
}


void Graff::Dijkstra(string start, string dest){
    /*Dijkstra's (greedy) shortest path algorithm to determine distances between point
    for the given Graff.
    */
    runT=0;
    vertex *u;  runT++;
    vertex *w;  runT++;
    vertex *s=NULL;  runT++;
    vertex *d=NULL;  runT++;
    visSet();
    d=Vfinder(dest,d);
    s=Vfinder(start,s);
    visSet();
    if(!s || !d){
        cout << "One or more objects of search doesn't exist" << endl;
        return;
    }
    if(d->district<0){
        if(s->district==1){
            BFS(*d,2);
            BFS(*s,1);
        }else
            BFS(*d,1);
        visSet();
    }
    for(int j = 0; j < vertices.size(); j++){
        vertices[j].distance = INT_MAX;
    }
    if(s->district != d->district){
        cout << "Path not found" << endl;
        return;
    }
    d->visited = false;
    s->visited = true; runT++;//visited origin
    s->distance = 0;  runT++;//distance to start is 0
    vector<vertex *> solved;  runT++;//vector/queue of solved vertices
    solved.push_back(s); runT++;
    vertex *t1, *t2; runT++;
    int minDistance; runT++;
    while(d->visited==false){
        int minDistance = INT_MAX; runT++;//initialize distance
        int h=0; runT++;
        for(int j=0; j<solved.size(); j++){
            u = solved[j]; runT++;
            for(int i=0; i<u->adj.size(); i++){//each vertex adjacent to u
                w=u->adj[i].v; runT++;
                if(w->visited==false){
                    //calc distance using u.distance and edge weight
                    int temp = u->distance + u->adj[i].weight; runT++;
                    //find min distance & store vertex info
                    if(temp < minDistance){
                        minDistance = temp; runT++;
                        //h = i;
                        t1 = u; runT++;
                        t2 = w; runT++;
                    }
                }
            }
        }
        solved.push_back(t2); runT++;
        t2->distance = minDistance; runT++;
        t2->visited = true; runT++;
        t2->previous = t1; runT++;
        //cout<<t2->distance<<endl;
    }
    cout<<t2->distance;
    versize=solved.size();
    for(int i=0;i<versize;i++){
        cout<<","<<solved[i]->name;
    }
    cout<<endl;
    rtimprint();
    versize=0;
}


queueVertex * Graff::BFSearch(std::string start, std::string destination){
    /*conducts a breadth-first search on the Graff, starting from the node containing
    'start' and ending at the node containing 'destination'.  Will not try to find paths
    that do not exist.*/
    runT=0;
    vertex *s=NULL;  runT++;
    vertex *d=NULL;  runT++;
    visSet();
    s=Vfinder(start,s);
    d=Vfinder(destination,d);
    if(!s || !d){
        cout << "One or more objects doesn't exist" << endl;
        return NULL;
    }
    s->visited=true;
    //Pseudocode:
    //void Graph::BFSearch(string startingCity, string destination){
        /*let Q be a queue
     Q.enqueue(v)
     label v as discovered
     while Q is not empty
        v ← Q.dequeue()
        for all edges from v to w in G.adjacentEdges(v) do
            if w is not labeled as discovered
                Q.enqueue(w)
                label w as discovered*/
    queue <vertex *> Q;  runT++;
    int i = 0;  runT++;
    vertex * v;  runT++;
    s->visited=true;
    s->distance=0;
    s->previous=NULL;
    v=s;
    Q.push(v);  runT++;
    v->visited = true;  runT++;
    vector<vertex *> ustor;  runT++;
    vertex *u;  runT++;
    ustor.push_back(v);  runT++;
    while(!Q.empty()){
        u = Q.front();  runT++;
        Q.pop();  runT++;
        for(i=0; i<u->adj.size(); i++){
            if(u->adj[i].v->visited == false){
                u->adj[i].v->visited = true;  runT++;
                vertex * t = u->adj[i].v;  runT++;
                t->distance = u->distance + 1;  runT++;
                t->previous = u;  runT++;
                vertex *n=t;  runT++;
                //Is destination found?  If so, print the answer
                if(t->name == destination){
                    cout<<t->distance;
                    vertex * n = t;  runT++;
                    vector<vertex *> thei;  runT++;
                    while(n!=NULL){
                        thei.push_back(n);  runT++;
                        n=n->previous;  runT++;
                    }
                    for(int j=thei.size()-1;j>=0;j--){
                        cout<<","<<thei[j]->name;
                    }
                    cout<<endl;
                    rtimprint();
                    return NULL;
                }
                Q.push(t);  runT++;
            }
        }
        u->visited = true;  runT++;
    }
    if(d->visited==false){
        cout<<"Path not found"<<endl;
    }
}


void Graff::findDistricts(){
    /*Determines which nodes contain connections, and sets a grouping
    variable contained in each node as needed*/
    runT=0;
    for(int i=0;i<vertices.size();i++){
        vertices[i].visited = false;  runT++;
    }
    queueVertex temp;  runT++;
    int dist = 1;  runT++;
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].visited == false){
            BFS(vertices[i], dist);  runT++;
            vertices[i].visited = true;  runT++;
            dist++;  runT++;
        }
    }
    rtimprint();
}


void Graff::BFS(vertex s, int k){
    /*Conducts a breadth-first search on the Graff to determine which nodes are
    connected, and sets a grouping variable contained in each node as needed*/
    s.visited = true;  runT++;
    s.district = k;  runT++;
    queue<vertex *> Q;  runT++;
    Q.push(&s);  runT++;
    vertex *u;  runT++;
    vertex *v;  runT++;
    while(!Q.empty()){
        u = Q.front();  runT++;
        Q.pop();  runT++;
        for(int i=0;i<u->adj.size();i++){
            v = u->adj[i].v;  runT++;
            if(v->visited==false){
                v->visited=true;  runT++;
                v->district = k;  runT++;
                v->previous = u;  runT++;
                Q.push(v);  runT++;
            }
        }
    }
}


void Graff::visSet(){
    /*Sets the initial conditions needed by every traversal/search/distance algorithm
    in this graph (Graff) implementation*/
    for(int j=0;j<vertices.size();j++){
        vertices[j].visited = false;  runT++;
        vertices[j].previous = NULL;   runT++;
        vertices[j].distance = 0;    runT++;
    }
}


vertex * Graff::Vfinder(string s,vertex * v){
    v=NULL;  runT++;
    int i=0; runT++;
    v=&vertices[i++]; runT++;
    while(i<vertices.size() && v->name!=s){
        v=&vertices[i++]; runT++;
    }
    return v;
}


queueVertex * Graff::DFSearch(string start, string destination){
    /*Conducts a depth-first search of the Graff to determine a connection between nodes.
    Returns the first connection found, which may not be the shortest*/
    runT=0;
    vertex *s;  runT++;
    vertex *d;  runT++;
    visSet();
    s=Vfinder(start,s);
    d=Vfinder(destination,d);
    if(!s || !d){
        cout << "One or more cities doesn't exist" << endl;
        return NULL;
    }
    if(s->district<0){
        BFS(*s,1);
        BFS(*d,2);
    }
    if(s->district != d->district){
        cout << "Path not found" << endl;
        return NULL;
    }
    s->visited=true;
    s->previous=NULL;
    //Pseudocode:
    //void Graph::DFSearch(string startingCity, string destination){
        /*let Q be a queue
     Q.enqueue(v)
     label v as discovered
     while Q is not empty
        v ← Q.dequeue()
        for all edges from v to w in G.adjacentEdges(v) do
            if w is not labeled as discovered
                Q.enqueue(w)
                label w as discovered*/
    vertex * v = s;  runT++;
    int i=0;  runT++;
    int j=0;  runT++;
    vector<vertex *> q;  runT++;
    q.push_back(v);  runT++;
    int m;  runT++;
    d->distance=1;  runT++;
    while(!q.empty()){
        v=q.back();  runT++;
        q.pop_back();  runT++;
        v->visited=true;  runT++;
        m=v->distance;  runT++;
        for(j=0;j < v->adj.size();j++){
            if(v->adj[i].v->visited == false){
                v->adj[i].v->previous = v;  runT++;
                q.push_back(v->adj[j].v);  runT++;
                v->adj[i].v->distance = m+1;  runT++;
            }
        }
    }
    vertex * t=d;
    while(t->previous!=NULL){
        cout<<t->name<<" -> ";
        t=t->previous;
    }
    cout<<endl<<d->distance<<endl;
    rtimprint();
}


int Graff::hashSum(string x, int s){
    /*Contains a hash-sum used by the hashtable contained within the Graff function.
    It is not to be confused with other hash-table functions potentionally used by a function
    calling Graff*/
    //x is string to hash, s is array size
    int sum = 0;  runT++;
    for(int i = 0;i<x.length();i++){
        sum += x[i];   runT++;//ascii char of ith val in string
    }
    sum = sum % s;  runT++;
    return sum;  runT++;
}



void Graff::delV(string name){
    /*Deletes the node containing the string name*/
    int i=0;
    while(vertices[i].name != name && i<vertices.size()){
        i++;
    }
    if(i>=vertices.size()){
        cout<<"Node "<<name<<" does not exist"<<endl;
    }
    vertices.erase(vertices.begin()+i);
}


void Graff::modAdjdel(string name,string s){
    /*Deletes a connection from the adjacency vertex of the name <s> of the
    node containing the name <name>*/
    int i=0;
    while(i<vertices.size() && vertices[i].name != name){
        i++;
    }
    if(i>=vertices.size()){
        cout<<"Node "<<name<<" does not exist"<<endl;
        return;
    }
    vertex * v=&vertices[i];
    i=0;
    while(i<v->adj.size() && v->adj[i].v->name != s){
        i++;
    }
    if(i>=v->adj.size()){
        cout<<name<<" is not connected to "<<s<<endl;
        return;
    }
    v->adj.erase(v->adj.begin()+i);
}


void Graff::rtimprint(){
    //Prints the runtime (runT).
    cout<<"Function running time: "<<runT<<endl;
}


void Graff::rsltprint(vertex * v){
    //prints the results of a given function from a vector of length versize
    for(int i=0;i < versize;i++){
        cout<<v[i].name<<" -> ";
    }
    cout<<endl<<v[versize-1].distance<<endl;
}

