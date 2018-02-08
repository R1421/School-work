/*Raymond Duncan
Rhonda Hoenigman
Assignment_5*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "movieTree.h"


using namespace std;

void displayMenu()
{
    cout<<"======Main Menu====="<<endl;
    cout<<"1. Find a movie"<<endl;
    cout<<"2. Rent a movie"<<endl;
    cout<<"3. Print the inventory"<<endl;
    cout<<"4. Quit"<<endl;
}

void buildMovieTree(MovieTree *tree, const char *fileName)
{
    ifstream file;
    file.open(fileName);
    if(file.fail()){
        cout<<"File didn't open"<<endl;
    }
    else{
        string line;
        string word;
        //Parameters for addMovie
        int rank;
        string name;
        int year;
        int quantity;


        while(!file.eof()){
            getline(file, line);
            stringstream ss(line);
            //cout<<line<<endl;
            for(int i = 0; i < 4; i++){
                getline(ss, word, ',');
                cout<<i<<" "<<word<<endl;
                //cout<<word<<endl;
                if(i == 0){
                    rank = atoi(word.c_str());
                }
                else if(i == 1){
                    name = word;
                }
                else if(i == 2){
                    year = atoi(word.c_str());
                }
                else{
                    quantity = atoi(word.c_str());
                }
            }

            tree->addMovieNode(rank, name, year, quantity);
            tree->printMovieInventory();
            cout<<endl<<endl;
        }
    }
}

int main()
{
    MovieTree *tree = new MovieTree;
    buildMovieTree(tree, "movies.txt");
    string input;
    while(true){
        displayMenu();
        cin>>input;

        //after the user enters an input
        if(atoi(input.c_str()) == 1){
            //Find a movie
        }
        else if(atoi(input.c_str()) == 2){
            //Rent a movie
        }
        else if(atoi(input.c_str()) == 3){
            //Print the inventory
        }
        else if(atoi(input.c_str()) == 4){
            //Quit
            break;
        }
        else{
            cout<<"That is not a valid input"<<endl;
        }
    }
}
