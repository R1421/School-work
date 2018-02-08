/*This program is a game where you encounter enemies and either fight or run away.
The user earns experience when defeating enemies.
When the user is killed, the game is over*/

#include "Creature.h"
#include "Healer.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//RandomEncounter causes the user to either encounter an enemy (2), a healer (3), or nothing (1)
int randomEncounter(){
    int randValue = rand() % 100 + 1;
    if(randValue % 2 == 0){
        return 2;
    }
    else if(randValue % 3 == 0){
        return 3;
    }
    else{
        return 1;
    }
}

int choices(string vs){
    int choice;
    cout<<"What would you like to do?"<<endl;

    //Is the encounter with a Healer, an Enemy, or nothing?
    if(vs == "Healer"){
        cout<<"1) Heal  2) Leave  3) End it"<<endl;
    }
    else if(vs == "Enemy"){
        cout<<"1) Fight  2) Escape  3) End it"<<endl;
    }
    else{
        cout<<"1) Stay 2) Explore  3) End it"<<endl;
    }

    //What does the user choose
    cin>>choice;
    if(choice == 2){
        return 2;
    }
    else if(choice == 3){
        return 3;
    }
    else if(choice == 1){
        return 1;
    }

    //Big suprise
    else{
        return 0;
    }
}

int main()
{
	/* The following code is just a test to see how the source code files and headers worked.

	cout<<"The code works"<<endl;
	Healer healer;
	cout<<endl;
	Enemy enemy;
	cout<<endl;
	Player player;
    */

	//First create the player
	Player player;
	bool vsEnemy = false;
	bool vsHealer = false;
	int action;
	int encounter;

	//Initialize game
	while(player.getAlive()){
		encounter = randomEncounter();
		if(encounter == 1){
			cout<<"There is nothing"<<endl;
			action = choices("Nothing");
			if(action == 3){
				cout<<"Game over"<<endl;
				player.killPlayer();
			}
			else if( action == 0){
				cout<<"A dragon swooped down from nowhere and ate you \n Game over"<<endl;
				player.killPlayer();
				}
			}
			else if(encounter == 2){
				cout<<"You've encountered an enemy!"<<endl;
				Enemy *enemy = new Enemy;
				vsEnemy = true;
				while(vsEnemy){
					action = choices("Enemy");
					if(action == 1){
						enemy->decrementHealth(player.attack());
						if(enemy->getHealth() <= 0){
							vsEnemy = false;
						}
					}
					else if(action == 2){
						if(player.escape()){
							vsEnemy = false;
							break;
						}
					}
					else{
						cout<<"Game over"<<endl;
						player.killPlayer();
					break;
					}
					if(vsEnemy){
						player.decrementHealth(enemy->attackPlayer());
						if(player.getHealth() <= 0){
                            player.killPlayer();
                            cout<<"You are dead"<<endl<<"Game over"<<endl;
                            break;
                        }
					}
				}
			}
			else{
				cout<<"You met a healer"<<endl;
				Healer *healer = new Healer;
				vsHealer = true;
				while(vsHealer){
					action = choices("Healer");
					if(action == 1){
						player.incrementHealth(healer->healPlayer());
						break;
					}
					else if(action == 2){
						vsHealer = false;
						break;
					}
					else{
					cout<<"Game over"<<endl;
					player.killPlayer();
					break;
				}
			}
		}
	}
}

