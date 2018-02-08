//Raymond Duncan
//Sina Aghli
//Assignment 9

/*This assignment will act as an encryptor and decryptor using the Caesar Cipher encryption method
The encryption key will be a changeable integer which is, by default, 5
*/
#include<unistd.h>
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

class Cipher{
private:
    string message;
    int key = 5;
public:
    Cipher(string input){
        message = input;
    }
    ~Cipher(){}
    void encrypt(){
        //The enctyption must take the inputs and add the key to the char value of each letter
        //If the number is larger than 126, the program must loop back to 32
        char c;
        int int_c;
        cout<<"The enctypted sentence is: "<<endl;
        for(int x = 0; x < message.length(); x++){
            c = message[x];
            //cout<<"The ASCII char is: "<<c<<endl;
            //cout<<"The number associated with character "<<x<<" is: "<<(int)c<<endl;
            int_c = (int)c;
            if(int_c + key > 126){
                int_c += (key - 94);
            }
            else{
                int_c += key;
            }
            //cout<<"The number associated with the encrypted character is: "<<int_c<<endl;
            cout<<(char)int_c;
        }
        cout<<endl;
    }
    void decrypt(){
        //The dectyption must take the inputs and subtract the key from the char value of each letter
        //If the number is smaller than 32, the program must loop back to 32
        char c;
        int int_c;
        cout<<"The decrypted sentence is: "<<endl;
        for(int x = 0; x < message.length(); x++){
            c = message[x];
            //cout<<"The ASCII char is: "<<c<<endl;
            //cout<<"The number associated with character "<<x<<" is: "<<(int)c<<endl;
            int_c = (int)c;
            if(int_c - key < 32){
                int_c -= (key - 94);
            }
            else{
                int_c -= key;
            }
            //cout<<"The number associated with the encrypted character is: "<<int_c<<endl;
            cout<<(char)int_c;
        }
        cout<<endl;
    }
};

int main(int argc, char*argv[])
{
    int c;
    bool encrypt = false;
    bool decrypt = false;
    bool fileIO = false;
    string input = "";
    while((c = getopt(argc, argv, "edf:"))!=-1){
        if(c == 'e'){
            encrypt = true;
        }
        if(c == 'd'){
            decrypt = true;
        }
        if(c == 'f'){
            fileIO = true;
            string fileName(optarg);
            ifstream inFile;
            inFile.open(fileName);
            string strLine;
            while(!inFile.eof()){
                getline(inFile, strLine);
                input.append(strLine);
            }
            inFile.close();
        }
    }
    //Now that all the flags have been checked, use the bool variables to run certain functions
    //Run the program using input from a txt file or
    if(!fileIO){
        cout<<"Enter a sentence"<<endl;
        getline(cin, input);
    }
    Cipher cipher1(input);

    if(encrypt){
        cipher1.encrypt();
    }
    if(decrypt){
        cipher1.decrypt();
    }



}
