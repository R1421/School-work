#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "movieTree.h"
#include "json/json.h"

using namespace std;

void displayMenu()
{
    cout<<"======Main Menu====="<<endl;
    cout<<"1. Rent a movie"<<endl;
    cout<<"2. Print the inventory"<<endl;
    cout<<"3. Delete a movie"<<endl;
    cout<<"4. Count the movies"<<endl;
    cout<<"5. Count longest path"<<endl;
    cout<<"6. Quit"<<endl;
}

int main()
{
    MovieTree *tree = new MovieTree("Assignment5Movies.txt");
    //buildMovieTree(tree, "Assignment5Movies.txt");
    string input;
    while(true){
        displayMenu();
        getline(cin, input);
        if(atoi(input.c_str()) == 1){
            //Rent a movie
            cout<<"Enter title:"<<endl;
            getline(cin, input);
            tree->rentMovie(input);
        }
        else if(atoi(input.c_str()) == 2){
            //Print the inventory
            tree->printMovieInventory();
        }
        else if(atoi(input.c_str()) == 3){
            //Delete the movie
            cout<<"Enter a title:"<<endl;
            getline(cin, input);
            tree->deleteMovieNode(input);
        }
        else if(atoi(input.c_str()) == 4){
            //Count the movies
            cout<<tree->countMovieNodes()<<endl;
        }
        else if(atoi(input.c_str()) == 5){
            //Count the longest path
        }
        else if(atoi(input.c_str()) == 6){
            //Quit
            cout<<"Goodbye!"<<endl;
            break;
        }
        else{
            cout<<"That is an invalid input"<<endl;
        }
        //cin.ignore(100, '\n');
    }
}
