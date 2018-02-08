#include "Player.h"
#include <iostream>

using namespace std;

Player::Player():Creature(){
	//cout<<"Calling Player Constructor"<<endl;
	level = 1;
	experience = 0;
	levelCap = 1000 + 100*(level - 1);
	escapes = 5;
	alive = true;
	strength = 30 + (level * 5);
	name = "Player";
	ctrType = "Player";
}

Player::~Player(){
	//cout<<"Calling Player Destructor"<<endl;
}

int Player::attack(){
	escapes++;
	experience += 50;
	cout<<"You dealt "<<strength<<" points of damage"<<endl;
	return strength;
}

int Player::defend(){
	return 2*strength;
}

void Player::incrementEXP(int EXP){
	if(experience + EXP >= levelCap){
		experience -= (levelCap - EXP);
		incrementLVL();
	}
	else{
		experience += EXP;
	}
}

void Player::incrementLVL(){
	level++;
}

bool Player::escape(){
	if(escapes > 0){
		escapes--;
		return true;
	}
	else{
		return false;
	}
}

bool Player::getAlive(){
	return alive;
}

void Player::killPlayer(){
	alive = false;
}
