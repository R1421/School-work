//This is a class for an enemy character
#include "Creature.h"

using namespace std;

#ifndef Enemy_h
#define Enemy_h

class Enemy: public Creature{
public:
	Enemy();
	~Enemy();
	int attackPlayer();
};

#endif
	
