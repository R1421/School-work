//This class is used for a healer character
#include "Creature.h"

//using namespace std;

#ifndef Healer_h
#define Healer_h

class Healer: public Creature{
private:
	int healStrength;
public:
	Healer();
	~Healer();
	int healPlayer();
};
#endif
	
