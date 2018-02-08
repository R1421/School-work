#include <iostream>
#include "movieTree.h"

using namespace std;


MovieTree::MovieTree()
{
    root = NULL;
}

MovieTree::~MovieTree()
{
    //Delete the tree
}

void MovieTree::printMovieInventory(MovieNode *node = root)
{
    //if(node != NULL){
        if(node->leftChild != NULL){
            printMovieInventory(node->leftChild);
        }
        if(node->rightChild != NULL){
            printMovieInventory(node->rightChild);
        }
    //}
    cout<<node->title<<endl;
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
    cout<<"Adding \""<<title<<"\" to tree!"<<endl;
    //Create the new node
    MovieNode *n = new MovieNode;
    n->title = title;
    n->quantity = quantity;
    n->year = releaseYear;
    n->ranking = ranking;
    n->leftChild = NULL;
    n->rightChild = NULL;


    MovieNode *item = root;
    MovieNode *P = NULL;

    while(item != NULL){
        P = root;  //Set the parent value
        if(title < item->title){    //Move pointer to the left
            item = item->leftChild;
            cout<<"L";
        }
        else{
            item = item->rightChild;
            cout<<"R";
        }
    }
    cout<<endl;
    n->parent = P;
    if(P == NULL){  //The tree is empty;
        root = n;
    }
    else{   //There are values in the tree
        item = n;
    }
}
