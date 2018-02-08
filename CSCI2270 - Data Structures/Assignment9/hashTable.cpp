#include <iostream>
#include "hashTable.h"

using namespace std;

HashTable::HashTable(int tSize)
{
    //Constructor
    //cout<<"test"<<endl;
    hashTable = new Movie *[tSize];
    tableSize = tSize;
    //cout<<"test"<<endl;
    for(int i = 0; i < tableSize; i++){
        cout<<i<<endl;
        hashTable[i] = new Movie;
        hashTable[i]->year = -1;
    }
}

HashTable::~HashTable()
{
    //Destructor
    Movie *s;   //Iterator node
    Movie *t;   //Placeholder node
    for(int i = 0; i < tableSize; i++){
        s = hashTable[i];
        while(s != NULL){
            t = s->next;
            //cout<<"Deleting: "<<s->title<<endl;
            delete s;
            //cout<<"test"<<endl;
            s = t;
            //cout<<"test"<<endl;
        }
    }
}


void HashTable::insertMovie(string title, int year)
{
    //insert a movie into the hash table
    int hashValue = hSum(title);
    if(hashTable[hashValue]->year == -1){
        //Add node to the location in the hash table
        hashTable[hashValue]->title = title;
        hashTable[hashValue]->year = year;
    }
    else{
        //There is a collision
        //Add the movie node to the end of the linked list at that value
        Movie *s = hashTable[hashValue];
        Movie *newMovie = new Movie;
        newMovie->title = title;
        newMovie->year = year;
        //newMovie->next = NULL;

        //Put the movies in alphabetic order
        if(title < s->title){
            //The movie comes first in the list
            newMovie->next = s;
            hashTable[hashValue] = newMovie;
        }
        else{
            //The movie comes in last or in the middle somewhere
            Movie *p = s;
            while(s->next != NULL){
                if(title < s->next->title){
                    //The movie comes before the next movie
                    break;
                }
                p = s;
                s = s->next;
            }
            if(s->next == NULL){
                //The movie goes at the end of the list
                s->next = newMovie;
                newMovie->next = NULL;
            }
            else{
                //The movie comes in the middle somewhere
                newMovie->next = p->next;
                p->next = newMovie;
                //newMovie->next = s->next;
            }
        }

        /*
        while(s->next != NULL){
            s = s->next;
        }
        s->next = newMovie;*/
    }
}

Movie* HashTable::findMovie(string title)
{
    //Locate a movie in the hash table
    int hashValue = hSum(title);
    //Two situations:  values stored in the hash location or not
    if(hashTable[hashValue] == NULL){
        cout<<"not found"<<endl;
    }
    else{
        //There may be a list of values in the list
        Movie *s = hashTable[hashValue];
        bool found = false;
        while(s != NULL){
            if(s->title == title){
                //The movie has been found
                found = true;
                break;
            }
            //cout<<"Test"<<endl;
            s = s->next;
        }
        if(found){
            //cout<<hashValue<<":"<<s->title<<":"<<s->year<<endl;
            return s;
        }
        else{
            //cout<<"not found"<<endl;
            return NULL;
        }
    }
}

void HashTable::deleteMovie(string title)
{
    //delete a movie from the list
    int hashValue = hSum(title);
    Movie *m = findMovie(title);
    //Movie is found or not
    if(m == NULL){
        //Movie does not exist
        cout<<"not found"<<endl;
    }
    else{
        if(hashTable[hashValue] == m){
            //The movie is at the head  of the linked list
            hashTable[hashValue] = m->next;
        }
        else{
            Movie *p = hashTable[hashValue];
            while(p->next != m){
                p = p->next;
            }
            if(m->next == NULL){
                //The movie is at the end of the list
                p->next = NULL;
            }
            else{
                //The movie is in the middle somewhere
                p->next = m->next;
            }
        }
        delete m;
    }

}

void HashTable::printInventory()
{
    //print the inventory
    Movie *s;   //Iterator node
    for(int i = 0; i < tableSize; i++){
        s = hashTable[i];
        while(s != NULL){
            if(s->year != -1){
                cout<<s->title<<" ("<<s->year<<")"<<endl;
            }
            s = s->next;
        }
    }
}

int HashTable::hSum(string title)
{
    //Output a hash value for the title of the movie
    int sum = 0;
    const char *t = title.c_str();
    //cout<<title.size()<<endl;
    for(int i = 0; i < title.size(); i++){
        sum += t[i];
    }
    sum = sum % tableSize;
    return sum;
}
