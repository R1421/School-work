#include "CommunicationNetwork.h"
#include <string>
#include <iostream>
using namespace std;

CommunicationNetwork::CommunicationNetwork(int QSize)
{
    queueSize = QSize;
    arrayQueue = new string[queueSize];

    //Set initial parameters for the linked list
    head = new node;
    head->previous = NULL;
    head->next = NULL;
    tail = new node;


    queueHead = 0;
    queueTail = 0;
}

//######################################################

CommunicationNetwork::~CommunicationNetwork()
{
    delete []arrayQueue;
}

//######################################################

//circular queue methods
void CommunicationNetwork::enqueue(string word)
{
    //cout<<"Queuing word"<<endl;
    arrayQueue[queueTail] = word;
    //queueTail++;
    if(queueTail == queueSize-1){   //Comparing index with size
        queueTail = 0;
    }
    else{
        queueTail++;
    }
    cout<<"E: "<<word<<endl;
    cout<<"H: "<<queueHead<<endl;
    cout<<"T: "<<queueTail<<endl;
}

//###############################################################

void CommunicationNetwork::dequeue() //should send through network, call transmit msg
{
    transmitMsg(arrayQueue[queueHead]);
    //queueHead++;
    if(queueHead == queueSize-1){ //queueHead index too high
        queueHead = 0;
    }
    else{
        queueHead++;
    }
    cout<<"H: "<<queueHead<<endl;
    cout<<"T: "<<queueTail<<endl;

}

//##############################################################

void CommunicationNetwork::printQueue()
{
    if(queueIsEmpty()){
        cout<<"Empty"<<endl;
        return;
    }
    for(int i = 0; i < queueSize; i++){
        cout<<i<<": "<<arrayQueue[i]<<endl;
    }
}

//#######################################################

void CommunicationNetwork::buildNetwork()
{
    //cout<<"Building network"<<endl;
    //Create the list of citits in the network
    string cityList[10] = {"Los Angeles","Phoenix","Denver","Dallas","St. Louis","Chicago","Atlanta","Washington, D.C.","New York","Boston"};

    //Delete the previous linked list
    node *n = head;
    while(n != NULL){
        //cout<<"Deleting "<<n->name<<endl;
        if(n->previous != NULL){    //When at the beginning of the linked list
            delete n->previous;
        }
        n = n->next;
    }
    delete n;

    //Create the linked list
    n = head;
    for(int i = 0; i < 10; i++){
        //cout<<i<<endl;
        if(i == 0){ //First item in the list
            node *n1 = new node;
            n->name = cityList[i];
            n->next = n1;
            n->next->previous = n;
            n = n->next;
        }
        else if(i == 9){    //Last item in the list
            n->next = NULL;
            n->name = cityList[i];
            tail = n;
        }
        else{   //All other items in the list
            node *n1 = new node;
            n->next = n1;
            n->name = cityList[i];
            n->next->previous = n;
            n = n->next;
        }
    }
    printPath();
}

//##########################################################

void CommunicationNetwork::printPath()
{
    //Print the current path of the network
    //cout<<"Printing Path"<<endl;
    cout<<"===CURRENT PATH==="<<endl;
    node *n = head;
    while(n->next != NULL){
        cout<<n->name<<" -> ";
        n = n->next;
    }
    cout<<n->name<<" -> NULL"<<endl;
    cout<<"=================="<<endl;

}

//#############################################################

bool CommunicationNetwork::queueIsFull() //send when full
{
    if(queueHead -1 == queueTail || queueHead + queueSize - 1 == queueTail){
        return true;
    }
    else{
        return false;
    }
}

//##############################################################

bool CommunicationNetwork::queueIsEmpty()
{
    if(queueHead == queueTail){
        //cout<<queueHead<<" = "<<queueTail<<endl;
        return true;
    }
    else{
        return false;
    }
}

//##############################################################

void CommunicationNetwork::transmitMsg(string word)
{
    //Send the message through the linked list and back
    node *n = head;
    n->message = word;
    while(n != NULL){   //Sendint the word forward through the list
        if(n->next != NULL){
            n->next->message = word;
        }
        cout<<n->name<<" recieved "<<n->message<<endl;
        n->message = "";
        n = n->next;
    }

    n = tail;
    n->message = word;
    while(n != NULL){   //Sending the word back through the list
        if(n->previous != NULL){
            n->previous->message = word;
        }
        cout<<n->name<<" received "<<n->message<<endl;
        n->message = "";
        n = n->previous;

    }
}
