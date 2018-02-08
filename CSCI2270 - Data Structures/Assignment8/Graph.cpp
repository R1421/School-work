#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <climits>
#include "Graph.h"

using namespace std;

Graph::Graph(string filename)
{
    //Constructor
    ifstream file;
    file.open(filename.c_str());

    if(file.fail()){
        cout<<"File could not be opened"<<endl;
    }
    else{
        string line;
        string word;

        //First create the list of vertices
        getline(file, line);
        stringstream ss(line);
        for(int i = 0; getline(ss, word, ','); i++){
            if(i != 0){
                addVertex(word);
                cout<<"Adding "<<word<<endl;
            }
        }

        //Now create the edges
        string name;
        int x = 0;
        while(!file.eof()){
            getline(file, line);
            cout<<endl<<line<<endl<<endl;;
            stringstream ss(line);
            for(int i = 0; getline(ss, word, ','); i++){
                cout<<word<<endl;
                if(i == 0){
                    name = word;
                }
                else if(atoi(word.c_str()) > 0){
                    if(i > x){
                        addEdge(name, vertices[i-1].name, atoi(word.c_str()));
                    }
                }
                //word = "";
            }
            x++;
        }

        //Initialize all ID values to be -1
        for(int i = 0; i < vertices.size(); i++){
            vertices[i].ID = -1;
        }

    }

}

Graph::~Graph()
{
    //Destructor
}

void Graph::addEdge(string name1, string name2, int weight)
{
    //add the edges
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == name1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == name2){
                    //both vertices have been found
                    //add the first adj vertex to the second's list
                    adjVertex av;
                    av.weight = weight;
                    av.v = &vertices[i];
                    vertices[j].adj.push_back(av);
                    cout<<"Adding edge: "<<vertices[j].name<<"***"<<vertices[i].name<<endl;

                    //now add the second to the first's list
                    av.v = &vertices[j];
                    vertices[i].adj.push_back(av);
                    cout<<"Adding edge: "<<vertices[i].name<<"***"<<vertices[j].name<<endl;
                }
            }
        }
    }

}

void Graph::addVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<n<<" found."<<endl;
            break;
        }
    }
    if(!found){
        //create new vertex
        vertex v;
        v.name = n;
        v.visited = false;
        vertices.push_back(v);
    }
}

void Graph::displayGraph()
{
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].ID<<": "<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(j == 0){
                cout<<vertices[i].adj[j].v->name;
            }
            else{
                cout<<"***"<<vertices[i].adj[j].v->name;
            }
        }
        cout<<endl;
    }
}

void Graph::findDistricts()
{
    //Reset vertices
    vertex *s = NULL;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].visited = false;
    }

    //Assign all vertices an ID
    int IDnum = 1;
    while(true){
        //Choose appropriate start vertex
        bool noID = false;  //Is there a vertex in vertices without an ID?
        for(int i = 0; i < vertices.size(); i++){
            if(vertices[i].ID == -1){
                s = &vertices[i];
                noID = true;
                break;
            }
        }
        if(noID){
            s->visited = true;
            s->ID = IDnum;
            cout<<s->name<<endl;
            queue<vector<adjVertex> > q;
            q.push(s->adj);

            while(q.size() > 0){
                vector<adjVertex> u = q.front();
                q.pop();
                for(int i = 0; i < u.size(); i++){
                    if(u[i].v->visited == false){
                        u[i].v->visited = true;
                        u[i].v->ID = IDnum;
                        cout<<u[i].v->name<<endl;
                        q.push(u[i].v->adj);
                    }
                }
            }
        }
        else{
            break;
        }
        IDnum++;
    }
}

void Graph::Dijkstra(string start, string finish)
{
    //Reset all nodes
    vertex *s = NULL;
    vertex *f = NULL;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].previous = NULL;
        vertices[i].visited = false;
        vertices[i].distance = INT_MAX;
        if(vertices[i].name == start){
            s = &vertices[i];
            //cout<<"s assigned"<<endl;
        }
        if(vertices[i].name == finish){
            f = &vertices[i];
            //cout<<"f assigned"<<endl;
        }
    }

    if(s == NULL || f == NULL){
        cout<<"One of the cities you entered is invalid"<<endl;
    }
    else if(s->ID != f->ID){
        cout<<"No safe path between those cities"<<endl;
    }
    else{
        s->visited = true;
        s->distance = 0;

        //Now perform the greedy search
        vector<vertex*> solved;
        solved.push_back(s);
        vertex *closest;
        int minDist;
        int Dist;
        while(!f->visited){
            minDist = INT_MAX;
            for(int i = 0; i < solved.size(); i++){
                for(int j = 0; j < solved[i]->adj.size(); j++){
                        if(!solved[i]->adj[j].v->visited){
                            //cout<<"Running"<<endl;
                            Dist = solved[i]->distance + solved[i]->adj[j].weight;
                            cout<<"Distance from "<<solved[i]->name<<" to "<<solved[i]->adj[j].v->name<<": "<<Dist<<endl;

                            if(Dist < minDist){
                                minDist = Dist;
                                closest = solved[i]->adj[j].v;
                                closest->previous = solved[i];
                        }

                    }
                }
            }
            //Calculate the closest node and add it to the solved list
            closest->visited = true;
            closest->distance = minDist;
            solved.push_back(closest);

        }
        //Check the distances of all nodes
        for(int i = 0; i < solved.size(); i++){
            cout<<solved[i]->name<<" - "<<solved[i]->distance<<endl;
            if(solved[i]->previous == NULL){
                cout<<"Previous node: NULL"<<endl;
            }
            else{
                cout<<"Previous node: "<<solved[i]->previous->name<<endl<<endl;
            }
        }

        //Print out the distance and path taken
        vector<vertex*> path;
        vertex *i = solved[solved.size()-1];
        cout<<i->distance<<endl;
        while(i != NULL){
            path.push_back(i);
            i = i->previous;
        }
        for(int x = path.size()-1; x > -1; x--){
            if(x == 0){
                cout<<path[x]->name<<endl;
            }
            else{
                cout<<path[x]->name<<"***";
            }
        }
    }
}

void Graph::shortestPath(string start, string finish)
{
    //Reset all nodes
    vertex *s = NULL;
    vertex *f = NULL;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].previous = NULL;
        vertices[i].visited = false;
        vertices[i].distance = INT_MAX;
        if(vertices[i].name == start){
            s = &vertices[i];
        }
        if(vertices[i].name == finish){
            f = &vertices[i];
        }
    }

    if(s == NULL || f == NULL){
        cout<<"One of the cities you entered is invalid"<<endl;
    }
    else if(s->ID == f->ID){
        s->visited = true;
        cout<<s->name<<endl;
        queue<vector<adjVertex> > q;
        q.push(s->adj);
        s->distance = 0;
        while(q.size() > 0){
            vector<adjVertex> u = q.front();
            vertex *prev = s;
            s = u[0].v;
            q.pop();
            for(int i = 0; i < u.size(); i++){
                if(u[i].v->visited == false){
                    u[i].v->visited = true;
                    cout<<u[i].v->name<<endl;
                    //How far is the node from the start?
                    //if(distance < u[i].v->distance){
                        u[i].v->distance = u->distance + 1;
                      //  u[i].v->previous = prev;
                    //}
                    q.push(u[i].v->adj);
                }
            }
            //distance++;
        }
        for(int i = 0; i < vertices.size(); i++){
            cout<<vertices[i].name<<" - "<<vertices[i].distance<<endl;
        }
        cout<<f->distance<<end;
    }
    else{
        cout<<"No safe path between citites"<<endl;
    }
}
