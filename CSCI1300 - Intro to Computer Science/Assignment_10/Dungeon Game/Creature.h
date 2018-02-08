//This is the class for the most basic of objects, the creature
#include <string>

using namespace std;

#ifndef Creature_h
#define Creature_h

class Creature{
protected:
	string ctrType;
	string name;
	int strength;
	int agility;
	int healthPoints;
public:
	Creature();
	~Creature();
	//When the creature takes damage
	void decrementHealth(int recAttack);
	//When the creature is healed
	void incrementHealth(int recHealth);
	//What is the creatures health
	int getHealth();
};

#endif
