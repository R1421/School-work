//Raymond Duncan
//Recitation Section 108
//Sina Aghli
#include <iostream>
#include <stdlib.h>

using namespace std;

//This class is used for keeping track of the number of bugs in the collection
class BugCollection{
private:
    int ants;
    int flies;
    int spiders;
public:
    //Construct the class
    BugCollection(int a, int f, int s){
    cout<<"Calling BugCollection constructor"<<endl;
    //Set each initial amount of bugs in the collection
    ants = a;
    flies = f;
    spiders = s;
    };
    ~BugCollection(){
    cout<<"Calling BugCollection destructor"<<endl;
    };

    //This method is used to increment the bug count of a certain type of bug
    void addBug(int bugType){
        //1 = ant, 2 = fly, 3 = spider
        if(bugType == 1)
            ants++;
        else if(bugType == 2)
            flies++;
        else if(bugType == 3)
            spiders++;
        else
            cout<<"That is not a valid input"<<endl;
    }

    //This method is used to remove a bug from the collection
    void removeBug(int bugType){
        //1 = ant, 2 = fly, 3 = spider
        if(bugType == 1)
            ants--;
        else if(bugType == 2)
            flies--;
        else if(bugType == 3)
            spiders--;
        else
            cout<<"That is not a valid input"<<endl;
    }

    //This method is used to print the number of each bug type in the collection
    void printCollection(){
        cout<<"There are currently "<<ants<<" ants,"<<endl;
        cout<<"There are "<<flies<<" flies , and"<<endl;
        cout<<"There are "<<spiders<<" spiders in the collection."<<endl;
    }
};


//The following function is used to find the min and the max values in an integer array
void findMinMax(int *intArray, int *maxV, int* minV){
    //Set the max values as
    maxV = NULL;
    minV = NULL;
    //Find the max value
    for(int x = 0; x < 100; x++){
        if(!intArray[x])
            break;
        if(!maxV)
            *maxV = intArray[x];
        else if(intArray[x] > *maxV)
            *maxV = intArray[x];
    }

    //Find the min value
    for(int x = 0; x < 100; x++){
        if(!intArray[x])
            break;
        if(!minV)
            *minV = intArray[x];
        else if(intArray[x] < *minV)
            *minV = intArray[x];

    }
}

int main()
{
    //Create an instance of bug collection that has 5 ants, 4 flies, and 6 spiders
    BugCollection collection(5,4,6);

    //Decrement the number of spiders by 1
    collection.removeBug(3);
    //Attempt to enter an invalid entry. There should be an exception
    collection.removeBug(4);

    //Increment the number of flies by 1
    collection.addBug(2);

    //There should be five of each type of bug in the collection
    collection.printCollection();

    //Create an array of 10 numbers
    int intArray[10];
    for(int x = 0; x < 10; x++){
        intArray[x] = x;
    }
    int *maxV;
    int *minV;

    findMinMax(intArray,maxV,minV);
    cout<<"The max is: "<<*maxV<<endl;
    cout<<"The min is: "<<*minV<<endl;
}
