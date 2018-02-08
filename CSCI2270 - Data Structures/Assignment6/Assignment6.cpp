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
    cout<<"5. Quit"<<endl;
}

void buildMovieTree(MovieTree *tree, string filename)
{
    json_object *jObj = json_object_new_object();

    json_object *jAdd = json_object_new_string("add");
    json_object *jOp1 = json_object_new_object();
    //json_object_object_add(jObj, "1", jAdd);

    json_object_object_add(jOp1, "operation", jAdd);
    json_object *jTitle = json_object_new_string("movie title");
    json_object_object_add(jOp1, "parameter", jTitle);
    json_object_object_add(jObj, "1", jOp1);

    json_object *jMovie = json_object_new_array();
    ifstream file;
    file.open(filename.c_str());

    if(file.fail()){
        cout<<"File could not open"<<endl;
    }
    else{
        //Values to be entered for every node
        int ranking;
        string title;
        int year;
        int quantity;


        string line;
        string word;
        while(!file.eof()){
            getline(file, line);
            if(line == ""){
                break;
            }
            stringstream ss(line);
            for(int i = 0; i < 4; i++){
                getline(ss, word, ',');
                if(i == 0){
                    ranking = atoi(word.c_str());
                }
                else if(i == 1){
                    title = word;
                }
                else if(i == 2){
                    year = atoi(word.c_str());
                }
                else if(i == 3){
                    quantity = atoi(word.c_str());
                }
            }
            json_object *jMovieAdd = json_object_new_string(title.c_str());
            json_object_array_add(jMovie, jMovieAdd);

            //Now that variables are stored for the movienode members
            //create new nodes
            tree->addMovieNode(ranking, title, year, quantity);
        }
        file.close();
        json_object_object_add(jOp1, "output", jMovie);
        cout<<json_object_to_json_string_ext(jObj, JSON_C_TO_STRING_PRETTY);
    }
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
