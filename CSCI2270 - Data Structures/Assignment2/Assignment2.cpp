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
int arrayDoubled = 0;

bool removeCommon(string word)
{
    bool isCommon = false;

    string commonWords[50] = {"the","be","to","of","and","a","in","that","have","i","it","for","not","on","with","he","as",
    "you","do","at","this","but","his","by","from","they","we","say","her","she","or","an","will","my","one","all","would",
    "there","their","what","so","up","out","if","about","who","get","which","go","me"};

    for(int i = 0; i < 50; i++){
        if(commonWords[i] == word){
            isCommon = true;
            break;
        }
    }
    return isCommon;

}

void printNmostCommon(int n, wordCounter *wordArray)
{
    //Print the n most common words
    wordCounter *wordList = new wordCounter[n];
    for(int i = 0; i < n; i++){
        wordList[i].counter = 0;
        for(int j = 0; j < arraySize; j++){
            if(i == 0 && wordArray[j].counter > wordList[i].counter){
                wordList[i] = wordArray[j];
            }
            else if(wordArray[j].counter > wordList[i].counter && wordArray[j].counter < wordList[i-1].counter){
                wordList[i] = wordArray[j];
            }
        }
        cout<<wordList[i].counter<<" - "<<wordList[i].word<<endl;
    }

}

void countWordFrequency(string word, wordCounter *Array)
{
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

wordCounter *doubleArray(wordCounter *wordArray)
{
    arrayDoubled++;
    //cout<<"Doubling array"<<endl;   //Create new array container
    wordCounter *newArray = new wordCounter[2*arrayCap];
    for(int i = 0; i < arrayCap; i++){  //Populate array
        newArray[i] = wordArray[i];
        //newArray[i].counter = wordArray[i].counter;
        //cout<<newArray[i].word<<" "<<newArray[i].counter<<endl;
    }
    arrayCap = arrayCap*2;
    //delete wordArray;
    delete[] wordArray;
    return newArray;   //Return array
}




int main(int argc, char *argv[])
{
    //Set the file to search and the number of words to output from the command line arguments
    char *file = argv[1];
    int nWords = atoi(argv[2]);
    //int nWords = 10;

    //Create an array to store the words in the text
    wordCounter *wordArray = new wordCounter[100];


    ifstream inFile;
    string currentWord;
    int nlPos;
    inFile.open(file);
    //inFile.open("Hemingway_edit.txt");

    //Make sure the file was opened
    if(inFile.fail()){
        cout<<"File didn't open"<<endl;
    }
    else{
         while(inFile >> currentWord){
            if(!removeCommon(currentWord)){
                //cout<<currentWord<<" "<<arraySize<<endl;
                countWordFrequency(currentWord, wordArray);
                nonCommonWords++;
            }
            if(arraySize == arrayCap){
                wordArray = doubleArray(wordArray);
            }
         }
    }

    /*cout<<"Printing array:"<<endl;
    for(int i = 0; i < arraySize; i++){
        cout<<wordArray[i].word<<" "<<wordArray[i].counter<<endl;
    }*/
    printNmostCommon(nWords, wordArray);
    cout<<"#"<<endl;
    cout<<"Array doubled: "<<arrayDoubled<<endl;
    cout<<"#"<<endl;
    cout<<"Unique non-common words: "<<arraySize<<endl;
    cout<<"#"<<endl;
    cout<<"Total non-common words: "<<nonCommonWords<<endl;

}
