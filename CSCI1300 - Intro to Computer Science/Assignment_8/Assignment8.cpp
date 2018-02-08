/*This is a program is a game called Treasure Hunt
The object of the game is to maximize the user's score by finding hidden treasures that decrease in value with every guess
In order to accomplish this task, Two classes must be established, the Gameboard class and the Treasure class
The user will choose the size of the gameboard and the number of treasures on the gameboard.
*/

#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<vector>

using namespace std;

//First to create the gameboard
class Gameboard{
private:
    int score = 0;
    int **grid;
    int *treasureArray;
public:
    Gameboard(int **boardArray){
        grid = boardArray;}
    void incrementScore(int addScore){
        score += addScore;}
    int getScore(){
        return score;}
    int searchTreasures(int x, int y){
        if(grid[x][y])
            {
                return true;
            }
        else
        {
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

//The following is a function which creates the gameboard and the treasures
 int **CreateArray(int boardSize, int treasureCt){
    int **aArray;
    aArray = new int *[boardSize];
    for(int y = 0; y < boardSize; y++)
    {
        cout<<aArray[y];
        aArray[y] = new int [boardSize];
    }
    cout<<aArray<<endl;
    //This part places the treasures at a certain point in the array
    for(int i = 0; i < treasureCt; i++){
        srand(time(NULL));
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        cout<<endl<<endl<<"Here are the original x and y: "<<x<<" "<<y<<endl;
        while(true){
            if (aArray[x][y]){
                cout<<"There is already a treasure there"<<endl;
                x = rand() %boardSize;
                cout<<"Here is the new x value: "<<x;
                y = rand() %boardSize;
                cout<<"Here is the new y value"<<y;
            }
            else{
                break;
            }
        }
        cout<<endl<<"These are the final x and y value: "<<x<<" "<<y<<endl;
        vector<pair<int, Treasure>> v;
        v.push_back(make_pair(0, treasure));
        aArray[x][y] = &treasure;
        aArray[x][y] = 1;
    }
    return aArray;
    }



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

    int **aArray = CreateArray(boardSize, treasureCt);
    //cout<<endl<<"This is aArray"<<aArray[1][1]<<endl;
    Gameboard board(aArray);

    /*
    for(int x = 0; x < boardSize; x++)
    {
        for(int y = 0; y < boardSize; y++)
        {
            cout<<aArray[x][y]<<endl;
        }
    }
    */

    while(true){
        cout<<"Please enter two integers for the x and y of the treasure"<<endl;
        int x;
        int y;
        cin>>x>>y;
        x,y --;

        //Now that there are values set for the x and y, check for values in the array
        board.searchTreasures(x,y);
    }
}
