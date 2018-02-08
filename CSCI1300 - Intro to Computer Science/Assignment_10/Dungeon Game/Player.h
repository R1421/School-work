//This is the class that is associated with the user.
#include "Creature.h"

using namespace std;

#ifndef Player_h
#define Player_h

class Player: public Creature{
private:
	int level;
	int experience;
	int levelCap;
	int escapes;
	bool alive;
public:
	Player();
	~Player();
	//User can move
	//User can attack
	int attack();
	//User can defend
	int defend();
	//User can heal
	//Player can gain experience
	void incrementEXP(int EXP);
	//User can level up
	void incrementLVL();
	//User can sometimes escape
	bool escape();
	//Check if the player is alive
	bool getAlive();
	//Kill the player
	void killPlayer();
};

#endif
