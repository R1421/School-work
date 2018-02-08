/*Raymond Duncan
CSCI 2270 Rhonda Hoenigman
Assignment 3*/

#include <iostream>
#include <fstream>

using namespace std;

struct city
{
    string name;
    string message;
    city *next = NULL;
};

city *clearNetwork(city *head)
{
    city *n = head;
    city *n2 = n->next;
    while(n->next != NULL){
        //cout<<"Deleting "<<n<<endl;
        delete n;
        n = n2;
        n2 = n2->next;
    }
    delete n;
    city *head2 = new city;
    return head2;
}

city *buildNetwork(city *head)
{
    //First create a placeholder for the next city node and the array with which the original network will be created
    city *n = head;
    string cityList[10] = {"Los Angeles","Phoenix","Denver","Dallas","St. Louis","Chicago","Atlanta","Washington, D.C.","New York","Boston"};
    int i = 0;  //Test variable

    //Then delete any items currently in the linked list
    head = clearNetwork(head);
    n = head;

    //Now recreate the linked list
    for(int i = 0; i < 10; i++){

        if(i != 9){
            city *n1 = new city;
            n->name = cityList[i];
            n->next = n1;
            n = n->next;
        }
        else{
            n->name = cityList[i];
        }
    }
    return head;
}

void printNetwork(city *head)
{
    cout<<"===CURRENT PATH==="<<endl;
    city *n = head;
    while(n != NULL){
        cout<<n->name<<" -> ";
        n = n->next;
    }
    cout<<" NULL"<<endl;
    cout<<"================="<<endl;
}

void transmitMessage(city *head)
{
    //Open the file
    ifstream file;
    string word;
    city *n;
    file.open("messageIn.txt");
    if(file.fail()){
        cout<<"File didn't open"<<endl;
    }
    else{
        //Perform read-in operation
        while(file >> word){
            n = head;
            n->message = word;
            while(n != NULL){
                //n->message = word;
                if(n->next != NULL){
                    n->next->message = n->message;

                }
                cout<<n->name<<" recieved "<<n->message<<endl;
                n->message = "";
                n = n->next;
            }
        }
    }
}

city *addCity(city *head)
{
    city *n = head;
    city *newCity = new city;
    string cityName;
    string previousCity;
    //cin.ignore(1000, '\n');
    cout<<"Enter a city name: ";
    //cin>>ws;
    cin.ignore(1, '\n');
    getline(cin,cityName);
    cout<<endl<<"Enter a previous city name: ";
    //cin>>ws;
    cin.ignore(0, '\n');
    getline(cin,previousCity);
    cout<<endl;

    newCity->name = cityName;
    //cin>>ws;

    while(n != NULL){
        if(n->name == previousCity){
            newCity->next = n->next;
            n->next = newCity;
            break;
        }
        n = n->next;
    }
    return head;
}

city *deleteCity(city *head, string cityName)
{
    city *n = head;
    city *n2 = new city;
    while(n != NULL){
        if(cityName == head->name){ //For the first city
            delete head;
            head = n->next;
            break;
        }
        else if(cityName == n->next->name && n->next->next == NULL){     //For the last city
            delete n->next;
            n->next = NULL;
        }
        else if(cityName == n->next->name){   //Any other city
            n2->next = n->next->next;
            delete n->next;
            n->next = n2->next;
            delete n2;
            break;
        }
        else if(n->next == NULL){
            cout<<"City not in network"<<endl;
        }
        n = n->next;
    }
    return head;
}


int main()
{
    //Initial variable allows program to run until quit is called
    bool running = true;

    //Other important variables
    city *head = new city;
    string cityDelete;


    while(true){
        cout<<"======Main Menu====="<<endl;
        cout<<"1. Build Network"<<endl;
        cout<<"2. Print Network Path"<<endl;
        cout<<"3. Transmit Message Coast-To-Coast"<<endl;
        cout<<"4. Add City"<<endl;
        cout<<"5. Delete City"<<endl;
        cout<<"6. Clear Network"<<endl;
        cout<<"7. Quit"<<endl;

        //Take the value that the user inputs and perform an action
        int input;
        cin>>input;
        if(input == 1){
            //Perform the build network function
            head = buildNetwork(head);
            printNetwork(head);
        }
        else if(input == 2){
            //Perform the Print Network Path function
            printNetwork(head);
        }
        else if(input == 3){
            //Perform the Transmit Message function
            transmitMessage(head);
        }
        else if(input == 4){
            //Perform the Add City function
            head = addCity(head);
        }
        else if(input == 5){
            //Perform the Delete city function
            cout<<"Enter a city"<<endl;
            //cin>>ws;
            cin.ignore(1000, '\n');
            getline(cin, cityDelete);
            head = deleteCity(head, cityDelete);
        }
        else if(input == 6){
            //Perform the Clear Network function
            head = clearNetwork(head);
        }
        else if(input == 7){
            //Quit the application
            running = false;
        }
        else{
            cout<<"That is an invalid input"<<endl;
        }
        cin.ignore(1000, '\n');


        if(!running){
            cout<<"Goodbye!"<<endl;
            break;
        }
    }

}

