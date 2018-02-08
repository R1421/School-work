/*Raymond Duncan
CSCI2270
Rhonda Hoenigman*/
#include <iostream>
#include <fstream>

using namespace std;

struct Item{
    string category;
    string action;
    int price;
};
int forSale = 0;
int wanted = 0;


void shiftArray(int start, int fin, Item * itemArray, int *operations){
    (*operations)++;
    /*
    cout<<endl<<"Original array:"<<endl;
    for(int x = 0; x < fin; x++){
        cout<<itemArray[x].category<<endl;
    }*/
    for(int i = start; i < fin-1; i++){
        (*operations)++;
        itemArray[i].category = itemArray[i+1].category;
        itemArray[i].action = itemArray[i+1].action;
        itemArray[i].price = itemArray[i+1].price;
        itemArray[i+1].category = "NONE";
    }

}


void compareAction(string currentItem, Item *itemArray, int *sold, int *operations){
    //Find length of the array
    int arrayLength = 0;
    for(int i = 0; i < 100; i++){   //Iterate through each element
        if (itemArray[i].category == "NONE")
            break;
        else
            arrayLength ++;
    }
    //cout<<"Array Length: "<<arrayLength<<endl;

    //Now split the line into three temporary variables
    int comma1 = currentItem.find_first_of(",");
    int comma2 = currentItem.find_last_of(",");
    //cout<<"<comma1><comma2>"<<endl<<comma1<<endl<<comma2<<endl;

    string category = currentItem.substr(0,comma1);
    string action = currentItem.substr(comma1+2,comma2-comma1-2);
    int price = atoi((currentItem.substr(comma2+1)).c_str());

    //Print the three item values for testing
    //cout<<"<Category><Action><Price>:"<<endl<<category<<endl<<action<<endl<<price<<endl;

    //Make the comparison with array items
    int space;  //For the shift array function
    int counter = 0;    //To potentially add item to array
    for(int i = 0; i < arrayLength; i++){
        (*operations)++;
        //cout<<"test1"<<endl;
        //The first part should work correctly

        if(itemArray[i].category == category){
            if(itemArray[i].action != action){
                if(action == "wanted"){ //Item is wanted
                    if(itemArray[i].price <= price){
                        wanted++;
                        cout<<itemArray[i].category<<" "<<itemArray[i].price<<endl;
                        itemArray[i].category = "NONE";
                        //space = i;
                        shiftArray(i,arrayLength,itemArray, operations);

                        (*sold)++;
                        break;
                    }
                }
                //If the item is for sale
                else{
                    if(itemArray[i].price >= price){
                        forSale++;
                        cout<<category<<" "<<price<<endl;
                        itemArray[i].category = "NONE";
                        //space = i;
                        shiftArray(i,arrayLength,itemArray, operations);

                        (*sold)++;
                        break;
                    }
                }
            }

        }
        counter++;
    }
    //cout<<counter<<endl<<arrayLength<<endl;
    //If there are no matches in the array
    if(counter == arrayLength){
        itemArray[arrayLength].category = category;
        itemArray[arrayLength].price = price;
        itemArray[arrayLength].action = action;
    }


}




int main(int argc, char **argv)
{
    //Take the name of the file from the terminal
    char *file = argv[1];
    //cout<<file<<endl;
    int soldCt = 0;
    int *ptrSold = &soldCt;
    int operations = 0;
    int *operCt = &operations;


    //Declare struct array
    Item * messageBoard  = new Item[100];
    /*Check the functionality of the structure array
    for(int i = 0; i < 100; i++){
        cout<<messageBoard[i].category<<endl;

    }*/
    //Set the value of the category variable of each struct to NULL
    //This will allow for easy Checking of the structArray values.
    for(int i = 0; i < 100; i++){
        messageBoard[i].category = "NONE";
        //cout<<messageBoard[i].category<<endl;
    }
    int arrayLength;

    //Open the file to be read
    ifstream inFile;//Streams to input from a file
    string strLine;
    //inFile.open(file);
    inFile.open("messageBoard.txt");
    if (inFile.fail()){
        cout<<"File didn't open"<<endl;
    }
    else{
        while(!inFile.eof()){   //Read lines and
            arrayLength = 0;
            operations++;
            getline(inFile,strLine);
            //cout<<strLine<<endl;
            compareAction(strLine, messageBoard, ptrSold, operCt);
            for(int x = 0; x < 100; x++){
                //cout<<messageBoard[x].category<<", "<<messageBoard[x].action<<", "<<messageBoard[x].price<<endl;
                if (messageBoard[x].category == "NONE")
                    break;
                else
                    arrayLength ++;
            }
        }
    }
    //cout<<endl;


    inFile.close();


    cout<<"#"<<endl;
    for(int x = 0; x < arrayLength; x++){
        cout<<messageBoard[x].category<<", "<<messageBoard[x].action<<", "<<messageBoard[x].price<<endl;
    }
    cout<<"#"<<endl;
    cout<<"operations:"<<operations<<endl;
    cout<<"<wanted> <forSale>"<<wanted<<" "<<forSale<<endl;
    /*
    cout << "Hello world!" << endl;
    */

    //return 0;
}
