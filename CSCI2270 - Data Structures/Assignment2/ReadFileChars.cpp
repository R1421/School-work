#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    char *input = argv[1];

    ifstream inFile;
    string word;
    inFile.open(input);

    if(inFile.fail()){
        cout<<"File not found"<<endl;
        word = input;
    }
    else{
        while(!inFile.eof()){
            getline(inFile, word, ' ');
            cout<<(char)word<<endl;
        }
    }
}
