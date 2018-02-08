#include <iostream>
#include <stdlib.h>
#include "hashTable.h"

using namespace std;

void displayMenu()
{
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Insert movie"<<endl;
    cout<<"2. Delete movie"<<endl;
    cout<<"3. Find movie"<<endl;//FIN
    cout<<"4. Print table contents"<<endl;//FIN
    cout<<"5. Quit"<<endl;//FIN
}

int main()
{
    HashTable hTable(10);

    string input;
    while(true){
        displayMenu();
        getline(cin, input);
        if(atoi(input.c_str()) == 1){
            //Insert Movie
            string title;
            string year;
            cout<<"Enter title:"<<endl;
            getline(cin, title);
            cout<<"Enter year:"<<endl;
            getline(cin, year);
            hTable.insertMovie(title, atoi(year.c_str()));
        }
        else if(atoi(input.c_str()) == 2){
            //Delete Movie
            cout<<"Enter title"<<endl;
            getline(cin, input);
            hTable.deleteMovie(input);
        }
        else if(atoi(input.c_str()) == 3){
            //Find Movie
            cout<<"Enter title"<<endl;
            getline(cin, input);
            Movie *m = hTable.findMovie(input);
            if(m == NULL){
                cout<<"not found"<<endl;
            }
            else{
                cout<<hTable.hSum(input)<<m->title<<":"<<m->year<<endl;
            }
        }
        else if(atoi(input.c_str()) == 4){
            //Print table of contents
            hTable.printInventory();
        }
        else if(atoi(input.c_str()) == 5){
            //Quit
            cout<<"Goodbye!"<<endl;
            break;
        }
        else{
            cout<<"That is an invalid input"<<endl;
        }
    }
}
