#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "movieTree.h"

using namespace std;

MovieTree::MovieTree(string filename)
{
    root = new MovieNode;
    //root = NULL;
    root->title = "NULL";
    root->leftChild = NULL;
    root->rightChild = NULL;
    //root->parent = NULL;
    int opCount = 0;
    json_object *Assignment6Output = json_object_new_object();




    //json_object *jObj = json_object_new_object();

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

            json_object *jMovie = json_object_new_array();


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
            opCount++;
            json_object *jAdd = json_object_new_string("add");
            json_object *jOp1 = json_object_new_object();

            json_object_object_add(jOp1, "operation", jAdd);
            json_object *jTitle = json_object_new_string("movie title");
            json_object_object_add(jOp1, "parameter", jTitle);
            string strCount;
            stringstream convert;
            convert<<opCount;
            convert>>strCount;
            json_object_object_add(Assignment6Output, strCount.c_str(), jOp1);

            json_object *jMovieAdd = json_object_new_string(title.c_str());
            json_object_array_add(jMovie, jMovieAdd);
            json_object_object_add(jOp1, "output", jMovie);

            //Now that variables are stored for the movienode members
            //create new nodes
            addMovieNode(ranking, title, year, quantity);
        }
        file.close();
        //cout<<json_object_to_json_string_ext(Assignment6Output, JSON_C_TO_STRING_PRETTY);
    }

}

MovieTree::~MovieTree()
{
    //Delete the movie tree
    DeleteAll(root);
}

void MovieTree::DeleteAll(MovieNode *node)
{
    MovieNode *n = node;
    if(n->leftChild != NULL){   //If there is a left child
        DeleteAll(n->leftChild);
    }
    if(n->rightChild != NULL){  //If there is a right child
        DeleteAll(n->rightChild);
    }
    delete n;
}

void MovieTree::printMovieInventory(MovieNode *node, json_object *traverseLog)
{
    MovieNode *n = node;
    json_object *jO;
    if(n->leftChild != NULL){   //If there is a left child
        printMovieInventory(n->leftChild, jO);
    }
    cout<<"Movie: "<<n->title<<endl;
    if(n->rightChild != NULL){  //If there is a right child
        printMovieInventory(n->rightChild, jO);
    }
}

void MovieTree::printMovieInventory()
{
    printMovieInventory(root, Assignment6Output);
}

int MovieTree::countMovieNodes(MovieNode *node)
{
    int count = 1;
    MovieNode *n = node;
    if(n->leftChild != NULL){
        count += countMovieNodes(n->leftChild);
    }
    if(n->rightChild != NULL){
        count += countMovieNodes(n->rightChild);
    }
    return count;
}

int MovieTree::countMovieNodes()
{
    countMovieNodes(root);
}

MovieNode *MovieTree::searchMovieTree(MovieNode *node, string title, json_object *traverseLog)
{
    MovieNode *n = node;
    MovieNode *P;
    //Iterate through each element in the tree until the value is found
    while(n != NULL){
        P = n;
        if(n->title == title){
            break;
        }
        else if(title < n->title){
            n = n->leftChild;
        }
        else if(title > n->title){
            n = n->rightChild;
        }
    }
    if(title == P->title){
        return P;
    }
    else{
        cout<<"Movie not found"<<endl;
        return NULL;
    }
}

void MovieTree::findMovie(string title)
{
    MovieNode *n = searchMovieTree(root, title, Assignment6Output);
    if(n != NULL){  //If the movie is in the tree
        cout<<"Movie Info:"<<endl;
        cout<<"==========="<<endl;
        cout<<"Ranking:"<<n->ranking<<endl;
        cout<<"Title:"<<n->title<<endl;
        cout<<"Year:"<<n->year;
        cout<<"Quantity"<<n->quantity;
    }
}

void MovieTree::rentMovie(string title)
{
    MovieNode *n = searchMovieTree(root, title, Assignment6Output);
    if(n != NULL){
        if(n->quantity == 0){
            cout<<"Movie out of stock."<<endl;
        }
        else{
            n->quantity--;
            cout<<"Movie has been rented."<<endl;
            cout<<"==========="<<endl;
            cout<<"Ranking:"<<n->ranking<<endl;
            cout<<"Title:"<<n->title<<endl;
            cout<<"Year:"<<n->year<<endl;
            cout<<"Quantity:"<<n->quantity<<endl;

            if(n->quantity == 0){
                deleteMovieNode(n->title);
            }
        }
    }
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
    //cout<<"Adding "<<title<<" to tree"<<endl;
    if(root->title == "NULL"){  //Initial value of the tree (tree root)
        root->title = title;
        root->ranking = ranking;
        root->year = releaseYear;
        root->quantity = quantity;
        root->parent = NULL;
    }
    else{
        MovieNode *n = root;
        MovieNode *P;

        while(n != NULL){
            P = n;  //Setting the parent value of the new node
            if(title < n->title){
                n = n->leftChild;
                //cout<<"L";
            }
            else{
                n = n->rightChild;
                //cout<<"R";
            }
        }
        //cout<<endl;
        //Now the position of the new node should have been determined
        //The next step is to allocate memory for the new node
        MovieNode *newNode = new MovieNode;
        if(title < P->title){   //The new node should be P's left child
            P->leftChild = newNode;
        }
        else{
            P->rightChild = newNode;
        }
        newNode->parent = P;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        newNode->title = title;
        newNode->ranking = ranking;
        newNode->year = releaseYear;
        newNode->quantity = quantity;
    }
}

void MovieTree::deleteMovieNode(string title)
{
    //Now the code to delete the node
    MovieNode *n;
    n = searchMovieTree(root, title, Assignment6Output);    //Create a variable with which to iterate through the tree
    if(n == NULL){
        //cout<<"Movie not found"<<endl;
        return;
    }
    else{
        //Delete the node and redirect the pointers
        //Three Cases
        if(n->rightChild == NULL && n->leftChild == NULL){
            if(n == n->parent->leftChild){
                n->parent->leftChild = NULL;
            }
            else{
                n->parent->rightChild = NULL;
            }
            delete n;
        }
        else if(n->leftChild != NULL && n->rightChild == NULL){
            if(n = n->parent->leftChild){
                n->parent->leftChild = n->leftChild;
            }
            else{
                n->parent->rightChild = n->leftChild;
            }
            delete n;
        }
        else if(n->leftChild == NULL && n->rightChild != NULL){
            if(n = n->parent->leftChild){
                n->parent->leftChild = n->rightChild;
            }
            else{
                n->parent->rightChild = n->rightChild;
            }
            delete n;
        }
        else{
            MovieNode *r = n->rightChild;
            if(r->leftChild == NULL){
                //Don't do anything with the node's right child
                r->parent = n->parent;
                r->leftChild = n->leftChild;
                n->leftChild->parent = r;
                if(n == n->parent->leftChild){
                    n->parent->leftChild = r;
                }
                else{
                    n->parent->rightChild = r;
                }
            }
            else{
                while(r->leftChild != NULL){
                    r = r->leftChild;
                }
                if(r->rightChild != NULL){
                    r->parent->leftChild = r->rightChild;
                    r->rightChild->parent = r->parent;
                }
                else{
                    r->parent->leftChild = NULL;
                }
                //Now r has been severed from the tree
                r->parent = n->parent;
                r->leftChild = n->leftChild;
                r->rightChild = n->rightChild;
                n->leftChild->parent = r;
                n->rightChild->parent = r;
                if(n->parent != NULL){
                    if(n == n->parent->leftChild){
                        n->parent->leftChild = r;
                    }
                    else{
                        n->parent->rightChild = r;
                    }
                }
                else{
                    root = r;
                }
            }
            delete n;
        }
    }
}
