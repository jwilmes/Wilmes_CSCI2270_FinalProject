/*Created by Justin Wilmes
    April, 2015
*/

#include "Graff.h"

using namespace std;

void menu(){
    cout<<"======  Menu:  ======"<<endl;
    cout<<"0.  Quit"<<endl;
    cout<<"1.  Add object name"<<endl;
    cout<<"2.  Add object connections"<<endl;
    cout<<"3.  Organize current graff"<<endl;
    cout<<"4.  Breadth-first search"<<endl;
    cout<<"5.  Depth-first search"<<endl;
    cout<<"6.  Dijkstra weighted search"<<endl;
    cout<<"7.  Delete an object"<<endl;
    cout<<"8.  Delete a connection"<<endl;
    cout<<"9.  Print Graff, unzoned"<<endl;
    cout<<"10. Print Graff, Zoned"<<endl;
}

Graff * citiesReadFile(Graff * G, char**a,int n){
    ifstream in_stream;
    string nam;
    string stemp;
    string sss;
    char * filnam = a[1];
    in_stream.open(filnam);
    if(!in_stream){
        cout<<"Could not open file."<<endl;
        return G;
    }
    vector<string> citnam;
    nam = "";
    getline(in_stream,nam);
    size_t ssiz = nam.find_first_of(',');
    size_t pos = nam.find_first_of(',');
    while(ssiz<=nam.size()){
        ssiz=nam.find_first_of(',',pos);
        stemp = nam.substr(pos,ssiz-pos);
        citnam.push_back(stemp);
        if(ssiz-pos > 0)
        G->addVertex(stemp);
        pos = ssiz+1;
    }
    while(!in_stream.eof()){
        int n = 0;
        getline(in_stream,sss);
        pos = sss.find_first_of(',');
        nam = sss.substr(0,pos);
        ssiz = pos;
        while(ssiz<=sss.size()){
            ssiz=sss.find_first_of(',',pos);
            stemp = sss.substr(pos,ssiz-pos);
            int temp=atoi(stemp.c_str());
            if(temp > 0){
                G->addEdge(nam,citnam[n],temp);
            }
            pos = ssiz+1;
            n++;
        }
    }
    return G;
}

int main(int argv, char ** argc){
/*Provides an interface to use the Graff.
    can take an input file, if it is set in the same
    way as the input file for the graph assignment.
    Example file setup:
    cities,Chicago,L.A.,Colorado Springs,Houston
    Chicago,0,1700,-1,800
    L.A.,1700,0,-1,1200
    Colorado Springs,-1,-1,0,600
    Houston,950,1200,800,0

    note that the city distances need not be the same in both directions


    Instructions on specific use are included in the
    run.
*/
    char ** c = argc;
    int a = argv;
    //set variables:
    Graff * G = new Graff();
    //read input file
    if(argv>1){
        G=citiesReadFile(G,c,a);
    }
    //set more variables
    int iit=1;
    string s1="";
    string s2="";
    int data;
    //inputs loop
    while(iit!=0 || s1 != "quit" || s1!="Quit" || iit!=11){
        menu();
        
        getline(cin,s1);
        if(s1=="quit"||s1=="Quit"||s1=="Break",s1=="break"||s1=="0"||s1=="11"){
            break;
        }
        iit=atoi(s1.c_str());
        if(iit==1){
            cout<<"Enter a name:"<<endl;
            
            getline(cin,s1);
            G->addVertex(s1);
        }else if(iit==2){
            cout<<"Enter item name:"<<endl;
            
            getline(cin,s1);
            cout<<"Enter connection's name:"<<endl;
            
            getline(cin,s2);
            cout<<"Enter weighting (integer, please):"<<endl;
            cin>>data;
            G->addEdge(s1,s2,data);
        }else if(iit==3){
            G->findDistricts();
            cout<<"Organized."<<endl;
        }else if(iit==4){
            cout<<"Enter start name:"<<endl;
            
            getline(cin,s1);
            cout<<"Enter destination name:"<<endl;
            
            getline(cin,s2);
            G->BFSearch(s1,s2);
        }else if(iit==5){
            cout<<"Enter start name:"<<endl;
            
            getline(cin,s1);
            cout<<"Enter destination name:"<<endl;
            
            getline(cin,s2);
            G->DFSearch(s1,s2);
        }else if(iit==6){
            cout<<"Enter start name:"<<endl;
            
            getline(cin,s1);
            cout<<"Enter destination name:"<<endl;
            
            getline(cin,s2);
            G->Dijkstra(s1,s2);
        }else if(iit==7){
            cout<<"Input node to delete"<<endl;
            
            getline(cin,s1);
            G->delV(s1);
        }else if(iit==8){
            cout<<"Input node to modify"<<endl;
            
            getline(cin,s1);
            cout<<"Input connection to delete"<<endl;
            
            getline(cin,s2);
            G->modAdjdel(s1,s2);
        }else if(iit==9){
            G->displayEdges();
        }else if(iit==10){
            G->displayVertices();
        }
    }
    //finished running
    delete G;
    return 0;
}
