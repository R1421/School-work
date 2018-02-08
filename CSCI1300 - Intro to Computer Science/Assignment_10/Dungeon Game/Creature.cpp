#include "Creature.h"
#include <iostream>
#include <string>

using namespace std;

Creature::Creature(){
	//cout<<"Calling Creature Constructor"<<endl;
	strength = 0;
	agility = 10;
	healthPoints = 100;
}

Creature::~Creature(){
	//cout<<"Calling Creature Destructor"<<endl;
}

void Creature::decrementHealth(int recAttack){
	//The creature loses health proportional to the recAttack
	healthPoints -= recAttack;
	cout<<name<<" has "<<healthPoints<<"HealthPoints"<<endl;
}

void Creature::incrementHealth(int recHealth){
	//The creature gains health proportional to recHealth
	healthPoints += recHealth;
	cout<<name<<" has "<<healthPoints<<"HealthPoints"<<endl;
}

int Creature::getHealth(){
	return healthPoints;
}
