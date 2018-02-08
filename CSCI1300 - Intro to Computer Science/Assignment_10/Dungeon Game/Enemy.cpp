#include "Enemy.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Enemy::Enemy():Creature(){
	//cout<<"Calling Enemy Constructor"<<endl;
	ctrType = "Enemy";
	name = "Enemy";
	strength = rand() %50 +1;
	agility = rand() %50 +1;
	healthPoints = 100;
}

Enemy::~Enemy(){
	//cout<<"Calling Enemy Destructor"<<endl;
}

int Enemy::attackPlayer(){
	cout<<"The enemy dealt "<<strength<<" points of damage"<<endl;
	return strength;
}
