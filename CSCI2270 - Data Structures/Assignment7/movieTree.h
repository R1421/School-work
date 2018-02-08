#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <json/json.h>

struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;
    bool isRed;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        // Now that we are using nil these NULL's should be overwritten in addMovieNode.
    	leftChild = NULL;
    	rightChild = NULL;
        parent = NULL;
        isRed = true;
    }

};

class MovieTree
{
        int opCount;

    public:
        MovieTree(std::string);
        virtual ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        bool isValid();
        int countLongestPath();
        //use this to return the json object from the class when you are ready to write it to a file
        json_object* getJsonObject();

    protected:

    private:
        void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void printMovieInventory(MovieNode * node, json_object * traverseLog);
        void rbAddFixup(MovieNode * node); // called after insert to fix tree
        void leftRotate(MovieNode * x);
        void rbDelete(MovieNode * z);
        void rightRotate(MovieNode * x);
        void rbDeleteFixup(MovieNode * node);
        void rbTransplant(MovieNode * u, MovieNode * v);
        int rbValid(MovieNode * node);
        int countMovieNodes(MovieNode *node);
        int countLongestPath(MovieNode *node);
        MovieNode* searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog);
        MovieNode *root;
        MovieNode *nil;
        // Count of how many operations we have done.
        //including the json_object in the class makes it global within the class, much easier to work with
        json_object * Assignment6Output;


};

#endif // MOVIETREE_H
