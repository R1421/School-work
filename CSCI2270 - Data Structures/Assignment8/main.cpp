#include <iostream>
#include <stdlib.h>
#include "Graph.h"

using namespace std;

void displayMenu()
{
    cout<<"======Main Menu====="<<endl;
    cout<<"1. Print vertices"<<endl;
    cout<<"2. Find districts"<<endl;
    cout<<"3. Find shortest path"<<endl;
    cout<<"4. Find shortest distance"<<endl;
    cout<<"5. Extra credit"<<endl;
    cout<<"6. Quit"<<endl;
}

int main(int argc, char *argv[])
{

    Graph *g = new Graph("zombieCities.txt");

    bool districts = false;
    string input;
    while(true){
        displayMenu();
        getline(cin, input);

        if(atoi(input.c_str()) == 1){
            //Print vertices
            g->displayGraph();
        }
        else if(atoi(input.c_str()) == 2){
            //Find Districts
            g->findDistricts();
            districts = true;
        }
        else if(atoi(input.c_str()) == 3){
            //Find shortest path
            if(!districts){
                cout<<"Please identify the districts before checking distances"<<endl;
            }
            else{
                string start;
                string finish;
                cout << "Enter a starting city:" << endl;
                getline(cin, start);
                cout << "Enter an ending city:" << endl;
                getline(cin, finish);
                g->shortestPath(start, finish);
            }
        }
        else if(atoi(input.c_str()) == 4){
            //Find shortest distance
            if(!districts){
                cout<<"Please identify the districts before checking distances"<<endl;
            }
            else{
                string start;
                string finish;
                cout << "Enter a starting city:" << endl;
                getline(cin, start);
                cout << "Enter an ending city:" << endl;
                getline(cin, finish);
                g->Dijkstra(start, finish);
            }
        }
        else if(atoi(input.c_str()) == 5){
            //Extra Credit
        }
        else if(atoi(input.c_str()) == 6){
            //Quit
            cout<<"Goodbye!"<<endl;
            break;
        }
        else{
            cout<<"Invalid input"<<endl;
        }

    }
}
