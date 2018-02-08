/*Raymond Duncan
Assignment2
Rhonda Hoenigman*/
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct wordCounter
{
    string word;
    int counter = 1;    //This is set to one because the first appearance of the word should come with count 1
};

int arraySize = 0;
int arrayCap = 100;
int nonCommonWords =0;

bool removeCommon(string word)
{
    bool isCommon = false;

    string commonWords[50] = {"the","be","to","of","and","they","in","that","have","i","it","for","not","on","with","he","as",
    "you","do","at","this","but","his","by","from","they","we","say","her","she","or","an","will","my","one","all","would",
    "there","their","what","so","up","out","if","about","who","get","which","go","me"};

    for(int i = 0; i < arraySize; i++){
        if(commonWords[i] == word){
            isCommon = true;
            break;
        }
    }
    return isCommon;

}

void countWordFrequency(string word, wordCounter *Array)
{
    /*
    if(removeCommon(word)){
        return;
    }*/
    //Initial situation (before words are stored in the array)
    if(arraySize == 0){
        Array[0].word = word;
        arraySize++;
    }
    else{
        bool wordInArray = false;
        for(int x = 0; x < arraySize; x++){
            //If the current word matches one already in the array
            if(Array[x].word == word){
                wordInArray = true;
                nonCommonWords++;
                Array[x].counter++; //Increment the count of the word
                break;
            }
        }
        if(!wordInArray){
            Array[arraySize].word = word;   //New Word in the array
            arraySize++;
        }
    }
}

void doubleArray(wordCounter *wordArray)
{
    cout<<"Doubling array"<<endl;
    wordCounter *newArray = new wordCounter[2*arraySize];
    for(int i = 0; i < arraySize; i++){
        newArray[i] = wordArray[i];
    }
    delete wordArray;
    wordArray = newArray;
    delete newArray;
}




int main(int argc, char *argv[])
{
    //Set the file to search and the number of words to output from the command line arguments
    char *file = argv[1];
    int commonWords = atoi(argv[2]);

    //Create an array to store the words in the text
    wordCounter *wordArray = new wordCounter[10000];


    ifstream inFile;
    string currentLine;
    string currentWord;
    int nlPos;
    //inFile.open(file);
    inFile.open("Hemingway_edit.txt");

    //Make sure the file was opened
    if(inFile.fail()){
        cout<<"File didn't open"<<endl;
    }
    else{

        stringstream iss;
        while(getline(inFile,currentLine)){
            iss << currentLine;

            while(getline(iss, currentWord, ' ')){
                if(currentWord != ""){
                    cout<<currentWord<<endl;
                    //Now that the word has been read in, it is necessary to count the times that it has been used thus far
                    countWordFrequency(currentWord, wordArray);
                }
                if(arraySize == arrayCap){
                    cout<<""<<endl;
                    //doubleArray(wordArray);
                }

            }
            iss.clear();

        }
    }

    cout<<"Printing array:"<<endl;
    for(int i = 0; i < 20; i++){
        cout<<wordArray[i].word<<" "<<wordArray[i].counter<<endl;
    }
    cout<<nonCommonWords<<endl;

}
