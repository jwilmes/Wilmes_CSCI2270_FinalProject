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
/*Prototype:
    Graff();

    Description:
    builds the "Graff" (graph) that is to be used.

    Example:
    Graff * G = new Graff();

    Precondition:
    No Graff of the name requested

    Postcondition:
    A new Graff exists that can be modified using the functions in Graff.h
*/
    runT=0;
    versize = 0;
}


Graff::~Graff(){
    /*Prototype:
    ~Graff();

    Description:
    Clears the content for the Graff.

    Example:
    delete G (note that G is a Graff *)

    Precondition:
    Graff exists

    Postcondition:
    vector variables within the Graff are cleared.
*/
    vertices.clear();
}


void Graff::addEdgeUND(string v1, string v2, int weight){
    /*Prototype:
    void addEdgeUND(string, string, int);

    Description:
    Adds edges (connections) for nodes already existing on the graph.
        Creates a non-directional path between the node containing v1 and the
        node containing v2.

    Example:
    addEdge("Freezer","Oven",5);

    Precondition:
    Expects two strings and an int.  Other input will cause glitches or crashes.  There should be more than one
    node/vertex in existences before trying to create connections.
    Postcondition:
    The adjacency matrix of the node 'v1' is updated to include a path to node 'v2' of weight 'weight'.
    */
    runT=0;
    int i;
    bool n=false;
    for(i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == v1){
            n=true;
            for(int j = 0; j < vertices.size(); j++){ //make sure start and end are both found before writing edge
                if(vertices[j]->name == v2 && i != j){
                    adjVertex av;          runT++; //make adjVertex
                    av.v = vertices[j];  runT++;  //set its pointer
                    av.weight = weight;   runT++;  //set weight
                    vertices[i]->adj.push_back(av); runT++;
                    //another vertex for edge in other direction (ensure symmetry for bidirectional edges)
                    adjVertex av2;
                    av2.v = vertices[i];
                    av2.weight = weight;
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
    if(n==false){
        cout<<"Origin of connection does not exist"<<endl;
    }
}

void Graff::addEdge(string v1, string v2, int weight){
    /*Prototype:
    void addEdge(string, string, int);

    Description:
    Adds edges (connections) for nodes already existing on the graph.
        Creates a connection of weight 'weight' starting from the node with name 'v1' and ending at the node
        with the name 'v2'.

    Example:
    addEdge("Freezer","Oven",5);

    Precondition:
    Expects two strings and an int.  Other input will cause glitches or crashes.  There should be more than one
    node/vertex in existences before trying to create connections.
    Postcondition:
    The adjacency matrix of the node 'v1' is updated to include a path to node 'v2' of weight 'weight'.
    */
    runT=0;
    int i;
    bool n=false;
    for(i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == v1){
            n=true;
            for(int j = 0; j < vertices.size(); j++){ //make sure start and end are both found before writing edge
                if(vertices[j]->name == v2 && i != j){
                    adjVertex av;          runT++; //make adjVertex
                    av.v = vertices[j];  runT++;  //set its pointer
                    av.weight = weight;   runT++;  //set weight
                    vertices[i]->adj.push_back(av); runT++;
                    //another vertex for edge in other direction (ensure symmetry for bidirectional edges)
                    /*adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
    if(n==false){
        cout<<"Origin of connection does not exist"<<endl;
    }
}


void Graff::addVertex(string n){
    /*Prototype:
    void addVertex(string);

    Description:
    Inserts nodes into the graph (Graff).  If a node already exists with the name requested, returns an
    error message stating so.

    Example:
    G->addVertex("Handerson");

    Precondition:
    No vertex of name 'n' exists.

    Postcondition:
    A new vertex of name 'n' is added to the array 'vertices'.
    */
    runT=0;
    bool found = false; runT++;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == n){
            found = true; runT++;
            cout<<vertices[i]->name<<" found.  Please enter a different name/item."<<endl;
        }
    }
    if(found == false){
        vertex *v = new vertex; runT++;
        v->district = -1; runT++;
        v->name = n; runT++;
        v->visited = false;runT++;
        vertices.push_back(v);runT++;
    }
}


void Graff::displayEdges(){
    /*Prototype:
    void displayEdges();

    Description:
    Displays all vertices and their connections.  Starts with the vertex at the beginning of the
    vertices array, and ends with the vertex at the end of that array.

    Example:
    G->displayEdges();

    Precondition:
    There are nodes/vertices already in existance, and at least one of them has a connection.
    Postcondition:
    The names of the vertices are displayed, along with the connections they have.
    */
    int i=0;
    for(i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<"-->";
        for(int j = 0; j < vertices[i]->adj.size(); j++){ //for each element in vertices
            cout<<vertices[i]->adj[j].v->name<<"***";
        }
        cout<<endl;
    }
    cout<<"Number of nodes: "<<i<<endl;
}


void Graff::displayVertices(){
    /*Prototype:
    void displayVertices();

    Description:
    Displays the vertices contained in each zone and the largest zone.  Zones are groupings of vertices
    that can only be accessed by other vertices within that zone.

    Example:
    G->displayVertices();

    Precondition:
    The Graff G has vertices.  It is best if the organizing function is called so that the zones are
    displayed; otherwise a "zones not determined" error is given.
    Postcondition:
    The zones are displayed, along with the vertices in each zone.
    */
    //loop through vertices:
    int i;
    int ar[vertices.size()];
    int t=0;
    for(i=0;i<vertices.size();i++){
        ar[i]=vertices[i]->district;
        if(ar[i]>t)
            t=ar[i];
    }
    if(t==0){
        cout<<"Zones not determined."<<endl;
        return;
    }
    int h=0;
    int p=0;
    int w=0;
    for(i = t; i > 0;i--){
        cout<<"Zone "<<i<<": ";
        for(int j=0;j<vertices.size();j++){
            if(vertices[j]->district==i){
                h++;
                cout<<vertices[j]->name<<",";
            }
        }
        if(h>p){
             p=h;
             w=i;
        }

    }
    cout<<endl<<"Total elements: "<<vertices.size()<<endl;
    cout<<"Largest grouping: "<<p<<" from zone: "<<w<<endl;
    return;
}


void Graff::BFTraversal(string starting){
    /*Prototype:
    void BFTransversal(string)

    Description:
    A breadth-first traversal through the graph to determine connections.  It's workings
    are similar to the BFS function, except that this function has the purpose of printing
    node connections rather than determining zones (districts).

    Example:
    G->BFTraversal("Bedroom");

    Precondition:
    Expects there to be vertices and the vertices to have connections.
    Postcondition:
    Displays the vertices and their connections as they are visited, starting from the node
    'starting' and ending when all nodes within a zone have been visited.
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
    queue <vertex *> Q; runT++;
    int i = 0;  runT++;
    vertex *v;  runT++;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i]->visited = false;  runT++;
    }
    for(int j = 0; j < vertices.size(); j++){
        if(vertices[j]->name == starting){
            v = vertices[j];  runT++;
            v->visited = true;  runT++;
        }
    }
    Q.push(v);   runT++;
    v->visited = true;  runT++;
    cout<<v->name<<endl;
    vertex *u;  runT++;
    while(!Q.empty()){
        u = Q.front();  runT++;
        Q.pop();
        if(u->name!=v->name)
            cout<<u->name<<endl;
        for(i=0; i<u->adj.size(); i++){
            if(u->adj[i].v->visited == false){
                u->adj[i].v->visited = true;  runT++;
                vertex * t = u->adj[i].v;  runT++;
                Q.push(t);  runT++;
            }
        }
    }
    rtimprint();
}


void Graff::Dijkstra(string start, string dest){
    /*Prototype:
    void Dijkstra(string,string);

    Description:
    Dijkstra's (greedy) shortest path algorithm to determine distances between point
    for the given Graff.  Expects the names of the starting and ending nodes; returns
    an error message if either node is not found, or if there is no possible path between
    them.

    Example:
    G->Dijkstra("Bed","Coffee");

    Precondition:
    The nodes requested should exist, otherwise an error message will be returned.
    Postcondition:
    An array containing each node within the shortest path is created, traversed, and printed.
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
            BFS(d,2);
            BFS(s,1);
        }else
            BFS(d,1);
        visSet();
    }
    for(int j = 0; j < vertices.size(); j++){
        vertices[j]->distance = INT_MAX;
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
    cout<<"Distance: "<<t2->distance<<endl;
    //versize=solved.size();
    /*for(int i=0;i<versize;i++){
        cout<<","<<solved[i]->name;
    }*/
    while(t2->previous){
        cout<<t2->name<<" <- ";
        t2=t2->previous;
    }
    cout<<t2->name<<endl;
    rtimprint();
    versize=0;
}


queueVertex * Graff::BFSearch(string start, string destination){
    /*Prototype:
    queueVertex * BFSearch(string,string);

    Description:
    Conducts a breadth-first search on the Graff, starting from the node containing
    'start' and ending at the node containing 'destination'.  Will not try to find paths
    that do not exist; will give an error message if such a path is requested.

    Example:
    G->BFSearch("Doorway","Shoe Rack");

    Precondition:
    Must input strings to avoid crashing.  The nodes containing 'start' and 'destination'
    should exist, otherwise will throw an error message.  There should also be a path between
    'start' and 'destination'.
    Postcondition:
    An array containing the path from 'start' to 'destination' search is created, traversed, and printed.
    */
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
    /*Prototype:
    void findDistricts();

    Description:
    Determines which nodes contain connections, and sets a grouping/zoning
    variable contained in each node as needed.

    Example:
    G->findDistricts();

    Precondition:
    Assumes that nodes exist and have connections.
    Postcondition:
    The vertex variable 'district' is set to an int pertaining to the zone which it is in.
    All nodes that are connected are sent to the same zone.
    */
    runT=0;
    for(int i=0;i<vertices.size();i++){
        vertices[i]->visited = false;  runT++;
    }
    queueVertex temp;  runT++;
    int dist = 1;  runT++;
    for(int i=0;i<vertices.size();i++){
        if(vertices[i]->visited == false){
            BFS(vertices[i], dist);  runT++;
            vertices[i]->visited = true;  runT++;
            dist++;  runT++;
        }
    }
    rtimprint();
}


void Graff::BFS(vertex *s, int k){
    /*Prototype:
    void BFS(vertex*, int);

    Description:
    Conducts a breadth-first search on the Graff to determine which nodes are
    connected, and sets a grouping variable contained in each node as needed.
    Is used by other functions to determine the connectivity of the Graff.

    Example:
    BFS(randomVertex,10);

    Precondition:
    The vertex* 's' should exist, otherwise will segmentation fault.
    Postcondition:
    The district variable for 's' and all vertices connected to it are set to the same value
    'k'.  This is useful for checking whether vertices are connected.
    */
    s->visited = true;  runT++;
    s->district = k;  runT++;
    queue<vertex *> Q;  runT++;
    Q.push(s);  runT++;
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
    /*Prototype:
    void visSet();

    Description:
    Sets the basic initial conditions required by most of the searching algorithms, the notable exception being
    the Dijkstra algorithm, which requires the distance variable to be set to INT_MAX.

    Example:
    visSet();

    Precondition:
    Expects there to be some vertices in existence.
    Postcondition:
    The 'visited' variable for each node/vertex is set to false, the 'previous' for each is set to NULL,
    and the 'distance' for each is set to 0.
    */
    for(int j=0;j<vertices.size();j++){
        vertices[j]->visited = false;  runT++;
        vertices[j]->previous = NULL;   runT++;
        vertices[j]->distance = 0;    runT++;
    }
}


vertex * Graff::Vfinder(string s,vertex * v){
    /*Prototype:
    vertex * Vfinder(string, vertex* );

    Description:
    Determines which node contains the name 's', and sets the pointer 'v' to point to that node.
    Returns a NULL pointer if no node of name 's' is found.

    Example:
    Vfinder("Garage", Garr);

    Precondition:
    Must be sent a string and vertex*, else will crash.  Assumes that there are vertices to find.
    Postcondition:
    Returns the address of the vertex of the name 's'.
    */
    v=NULL;  runT++;
    int i=0; runT++;
    v=vertices[i++]; runT++;
    while(i<vertices.size() && v->name!=s){
        v=vertices[i++]; runT++;
    }
    return v;
}


queueVertex * Graff::DFSearch(string start, string destination){
    /*Prototype:
    queueVertex * DFSearch(string, destination)

    Description:
    Conducts a depth-first search of the Graff to determine a connection between nodes.
    Returns the first connection route found, which may not be the shortest

    Example:
    G->DFSearch("Attic","Cellar");

    Precondition:
    Assumes that there are nodes 'start' and 'destination', and that they are connected; otherwise
    throws an error.
    Postcondition:
    Creates and prints an array containing all the vertices on the path searched before finding
    'destination'.
    */
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
    if(d->district<0){
        if(s->district==1){
            BFS(d,2);
            BFS(s,1);
        }else
            BFS(d,1);
        visSet();
    }
    if(s->district != d->district){
        cout << "Path not found" << endl;
        return NULL;
    }
    s->visited=true;
    s->previous=NULL;
    //Pseudocode:
    //void Graph::DFSearch(string startingCity, string destination){
    /*
    for each vertex u in G.V except origin
    o.visited = true
    S=empty //(stack)
    S.push(o)
    while S is not empty
        u = S.pop()
        output u
        for all edges v in G.adjacentEdges(u)
            if v.visited = false
                v.visited = true
                S.push(v)
    */
    vertex * v = s;  runT++;
    int i=0;  runT++;
    int j=0;  runT++;
    vector<vertex *> q;  runT++;
    q.push_back(v);  runT++;
    v->visited=true;
    int m=0;  runT++;
    d->distance=1;  runT++;
    while(!q.empty()){
        v=q.back();  runT++;
        q.pop_back();  runT++;
        //v->visited=true;  runT++;
        m=v->distance;  runT++;
        for(j=0;j < v->adj.size();j++){
            if(v->adj[j].v->visited == false){
                v->adj[j].v->previous = v;  runT++;
                v->adj[j].v->visited = true;
                q.push_back(v->adj[j].v);  runT++;
                v->adj[j].v->distance = m+1;  runT++;
            }
        }
    }
    cout<<v->distance<<endl;
    vertex * t=d;
    cout<<t->name;
    t=t->previous;
    bool chc = false;
    for(int i=0;i<s->adj.size();i++){
        if(s->adj[i].v->name == t->name)
            chc=true;
    }
    while(t->previous!=NULL){
        cout<<" <- "<<t->name;
        t=t->previous;
    }
    if(chc==true)
        cout<<" <-" <<s->name;
    cout<<endl<<"Distance: "<<d->distance<<endl;
    rtimprint();
}



void Graff::delV(string name){
    /*Prototype:
    void delV(string);

    Description:
    Deletes the node containing the string 'name'; if no node contains 'name', then
    will send an error message explaining that there is no node containing 'name' and
    return.

    Example:
    G->delV("Useless Wall");

    Precondition:
    The object to be deleted should exist.
    Postcondition:
    The object of name 'name' is removed from 'vertices' and the connection arrays of every node
    that connected to it.
    */
    int h=0;
    //find node
    while(vertices[h]->name != name && h<vertices.size()){
        h++;
    }
    if(h>=vertices.size()){
        cout<<"Node "<<name<<" does not exist"<<endl;
        return;
    }else{
    vertex * a=vertices[h];
    vertex * temp;
    //delete connections to node
    for(int i=0;i<vertices.size();i++){
        for(int j=0;j<vertices[i]->adj.size();j++){
            temp = vertices[i];
            if(temp->adj[j].v==a){
                modAdjdel(temp->name,name);
            }
        }
    }
    //delete node
    cout<<"Deleting "<<a->name<<" from position "<<h<<endl;
    vertices.erase(vertices.begin()+h);
    }
}


void Graff::modAdjdel(string name,string s){
    /*Prototype:
    void modAdjDel(string, string);

    Description:
    Deletes a connection from the adjacency vertex of the name 's' of the
    node containing the name 'name'.  If there is no node with 'name' or
    no connection 's', will explain that no such node/connection exists and
    return.

    Example:
    G->modAdjdel("Living Room","Garage");

    Precondition:
    The vertex 'name' should exist and be connected to the vertex 's'.
    Postcondition:
    The vertex 's' is removed from the connections (adj) array of the vertex 'name'.
    */
    int i=0;
    while(i<vertices.size() && vertices[i]->name != name){
        i++;
    }
    if(i>=vertices.size()){
        cout<<"Node "<<name<<" does not exist"<<endl;
        return;
    }
    vertex * v=vertices[i];
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
    /*Prototype:
    void rtimprint();
    Description:
    Prints the runtime (runT).
        Will return the runtime of the last run function that tracks the
        runtime (using the variable runT).

    Example:
    rtimprint();

    Precondition:
    Another function that tracks the runtime should have been run recently.  Assumes the runtime has
    been reset before running the last function to track the runtime.
    Postcondition:
    The number of real operations are printed on the screen.
    */
    cout<<"Function running time: "<<runT<<endl;
}


void Graff::rsltprint(vertex * v){
    /*Prototype:
    void rslprint(vertex *);

    Description:
    prints the results of a given function from a vector of length versize.  rsl stands for results.

    Example:
    reslprint(something);
    (something is an array of vectors, length versize).

    Precondition:
    Assumes that the vector given exists - a NULL vector causes crashes.
    Postcondition:
    The name of each vector in 'v' is printed to the screen.
    */
    for(int i=0;i < versize;i++){
        cout<<v[i].name<<" -> ";
    }
    cout<<endl<<v[versize-1].distance<<endl;
}

