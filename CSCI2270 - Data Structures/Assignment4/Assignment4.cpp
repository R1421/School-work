#include <iostream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

string *buildWordArray()
{
    string word;
    ifstream file;
    string *wordArray = new string[23];
    file.open("messageIn.txt");
    if(file.fail()){
        cout<<"File couldn't open"<<endl;
    }
    else{
        int i = 0;
        while(file >> word){
            wordArray[i] = word;
            //cout<<wordArray[i]<<endl;
            i++;
        }
    }
    return wordArray;
}

void displayMenu()
{
    cout<<"======Main Menu====="<<endl;
    cout<<"1. Build Network"<<endl;
    cout<<"2. Print Network Path"<<endl;
    cout<<"3. Enqueue"<<endl;
    cout<<"4. Dequeue"<<endl;
    cout<<"5. Print Queue"<<endl;
    cout<<"6. Send Entire Message"<<endl;
    cout<<"7. Quit"<<endl;
}

int main()
{
    string *wordArray;
    wordArray = buildWordArray();
    int index = 0;
    bool network = false;

    CommunicationNetwork network1(10);

    //Take the value that the user inputs and perform an action
    while(true){
        displayMenu();
        int input;
        cin>>input;
        if(input == 1){
            //Perform the build network function
            if(network){
                cout<<"Network has already been created"<<endl;
            }
            else{
                network1.buildNetwork();
                network = true;
            }
        }
        else if(input == 2){
            //Perform the Print Network Path function
            network1.printPath();

        }
        else if(input == 3){
            //Perform the Enqueue function
            if(index == 23){    //This is the end of the message
                cout<<"No more words to queue"<<endl;
            }
            else if(!network1.queueIsFull()){
                network1.enqueue(wordArray[index]);
                index++;
            }
            else{
                cout<<"Oueue is full."<<endl;
            }
        }
        else if(input == 4){
            //Perform the Dequeue function
            if(!network){
                cout<<"Build a network before attempting to transmit a message."<<endl;
            }
            else if(!network1.queueIsEmpty()){
                network1.dequeue();
            }
            else{
                cout<<"Queue is empty."<<endl;
            }
        }
        else if(input == 5){
            //Perform the Print Queue city function
            if(network1.queueIsEmpty()){
                cout<<"Empty"<<endl;
            }
            else{
                network1.printQueue();
            }
        }
        else if(input == 6){
            //Perform the Send Entire Message function
            if(!network){
                cout<<"Build a network before attempting to transmit a message."<<endl;
            }
            else{
                while(index < 23){
                    while(!network1.queueIsFull() && index < 23){   //Fill queue while there are words to enqueue
                        network1.enqueue(wordArray[index]);
                        index++;
                    }
                    while(!network1.queueIsEmpty()){    //Dequeue until queue is empty
                        network1.dequeue();
                    }
                }
            }
        }
        else if(input == 7){
            //Quit the application
            cout<<"Goodbye!"<<endl;
            break;
        }
        else{
            cout<<"That is an invalid input"<<endl;
        }
        cin.ignore(1000, '\n');
    }
}
