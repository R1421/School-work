#include "Healer.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Healer::Healer():Creature(){
	//cout<<"Calling Healer Constructor"<<endl;
	ctrType = "Healer";
	name = "Healer";
	healStrength = rand() % 100 + 1;
}

Healer::~Healer(){
	//cout<<"Calling Healer Destructor"<<endl;
}

int Healer::healPlayer(){
	cout<<"The healer restored "<<healStrength<<" health points"<<endl;
	return healStrength;
}
