#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <vector>

using namespace std;

class FileIO{
private:
    string fileName;
    ifstream fileIO;
public:
    FileIO(string file){
        fileName = file;
    }
    ~FileIO(){};


    void CountLines(){
        int counter = 0;
        int n;
        bool inComment = false;
        fileIO.open(fileName);
        string line;
        while(!fileIO.eof()){
            getline(fileIO, line);

            n = line.find_first_not_of(" \t#{}");
            //Is the counter inside a comment?
            if(!inComment){
                                //If the there is a regular comment
                if(!((line[n] == '/' && (line[n+1] == '/' || line[n+1] == '*'))||(n == -1))){

                    counter ++;
                }

                //Is there a block comment?
                if (line[n] == '/' && line[n+1] == '*'){
                    //cout<<"Entering block comment"<<endl;
                    inComment = true;
                }
                //cout<<line<<endl;
            }
            //The counter is inside a block comment
            else{
                n = line.find_first_of("*");
                //cout<<line<<endl;
                if(line[n+1] == '/'){
                    //cout<<"Exiting block comment"<<endl;
                    inComment = false;
                }
            }
        }
        cout<<counter<<endl;
        cout<<"Closing "<<fileName<<endl;
        fileIO.close();
    }
};



int main()
{
    string fileName;
    ifstream listFile;
    listFile.open("Dungeon_Game_Files.txt");

    if(listFile.fail()){
        cout<<"There was a problem opening the file"<<endl;
    }
    else{
        while(!listFile.eof()){
            getline(listFile, fileName);
            cout<<fileName<<endl;
            FileIO file1(fileName);
            file1.CountLines();
            cout<<"test1"<<endl;
        }
        cout<<"test2"<<endl;
    }
    cout<<"test3"<<endl;
    listFile.close();

}
