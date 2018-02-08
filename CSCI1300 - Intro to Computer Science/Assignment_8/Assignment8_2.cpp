////Raymond Duncan
//Sina Aghli


/*This is a program is a game called Treasure Hunt
The object of the game is to maximize the user's score by finding hidden treasures that decrease in value with every guess
In order to accomplish this task, Two classes must be established, the Gameboard class and the Treasure class
The user will choose the size of the gameboard and the number of treasures on the gameboard.
*/

#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<vector>
#include<ctgmath>

using namespace std;

//First to create the gameboard
class Gameboard{
private:
    int score = 0;
    int **grid;
    int *treasureArray;
    int Board;
public:
    Gameboard(int boardSize, int treasureCt){
        CreateArray(boardSize, treasureCt);
        Board = boardSize;
        cout<<Board<<endl;
    }
    Gameboard(int **boardArray){
        grid = boardArray;}
    void incrementScore(int addScore){
        score += addScore;}
    int getScore(){
        return score;}
    int searchTreasures(int x, int y){
        if(x > Board-1 || x < 0){
            cout<<"Those coordinates are not in the domain of the board"<<endl;
            return false;
        }
        else if(y > Board-1 || y < 0){
            cout<<"Those coordinates are not in the domain of the board"<<endl;
            return false;
        }
        else if(grid[x][y])
            {
                cout<<"There is a treasure there"<<endl;
                return true;
            }
        else
        {
            cout<<"There is no treasure there"<<endl;
            return false;
        }
    }
    void checkTreasures(int x, int y){
        if(grid[x][y]){
            cout<<"You found a treasure!"<<endl;
            grid[x][y] = 0;
        }
        else
        {
            cout<<"There is not any treasure there"<<endl;
        }
    }
    //The following is a function which creates the gameboard and the treasures
    void CreateArray(int boardSize, int treasureCt){
        grid = new int *[boardSize];
        for(int y = 0; y < boardSize; y++)
        {
            cout<<grid[y];
            grid[y] = new int [boardSize];
        }
        cout<<grid<<endl;
        //This part places the treasures at a certain point in the array
        for(int i = 0; i < treasureCt; i++){
            srand(time(NULL));
            int x = rand() % boardSize;
            int y = rand() % boardSize;
            cout<<endl<<endl<<"Here are the original x and y: "<<x<<" "<<y<<endl;
            while(true){
                if (grid[x][y]){
                    cout<<"There is already a treasure there"<<endl;
                    x = rand() %boardSize;
                    cout<<"Here is the new x value: "<<x<<endl;
                    y = rand() %boardSize;
                    cout<<"Here is the new y value: "<<y<<endl;
                }
                else{
                    break;
                }
            }
            cout<<endl<<"These are the final x and y value: "<<x<<" "<<y<<endl;
            grid[x][y] = 1;
        }

    }
    void deleteTreasure(int * treasureLocation){
        ~*treasureLocation;
    }

};

//Now the treasure class
class Treasure{
private:
    int points;
    int x;
    int y;
public:
    Treasure(){
        points = rand() % 100 + 1;
    };
    ~Treasure();
    void decrementPoints(){
        points *= .9;
    }
};




int main()
{
    //This is where the game will be run
    //First create the gameboard and the treasures
    int treasureCt;
    int boardSize;
    cout<<"Enter a value for the size of the grid"<<endl;
    cin>>boardSize;
    cout<<"Enter a value for the number of treasures"<<endl;
    cin>>treasureCt;

    Gameboard board(boardSize,treasureCt);
    //CreateArray(boardSize, treasureCt);
    //cout<<endl<<"This is aArray"<<aArray[1][1]<<endl;


    /*
    for(int x = 0; x < boardSize; x++)
    {
        for(int y = 0; y < boardSize; y++)
        {
            cout<<aArray[x][y]<<endl;
        }
    }
    */

    int guesses = 0;
    int score;
    double factor;
    //Initiate the game
    while(true){
        cout<<"Please enter two integers for the x and y of the treasure"<<endl;
        int x;
        int y;
        cin>>x>>y;
        x--;
        y--;

        //Now that there are values set for the x and y, check for values in the array
        if(board.searchTreasures(x,y)){
            factor = pow(.9,guesses);
            score = (rand() % 100 + 1)*factor;
            board.incrementScore(score);
            cout<<"The treasure had "<<score<<" points"<<endl<<"Your score is now: "<<board.getScore()<<endl;
            treasureCt--;
        }
        else{
            guesses++;
        }
        if(treasureCt == 0){
            break;
        }
    }
}
