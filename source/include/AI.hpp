#ifndef __AI_HPP
#define __AI_HPP

#include <vector>

#include "fuzzy.hpp"
#include "neuralnet.hpp"

enum NpcTeamActions{
	defensive = 0,
	coverAttack = 1,
	allAttack =2,
	idle = 3,
	runaway = 4

};

enum NpcAction{
	RUNAWAY = 0,
	IDLE = 1,
	DEFENSIVE = 2,
	LOW_ATTACK = 3,
	HIGH_ATTACK = 4

};

class NPCPlayers
{
public:		
	NPCPlayers();
	~NPCPlayers();
private:
	float health;
	float ammo;
	float distance_to_player;

	NpcAction currentAction;

	Fuzzy* fuzzy;
	NeuralNetwork* neuralnet;

public:
	void actionSelection();

	void setHealth(float);
	void setAmmo(float);
	void setDistance(float);
};

/*class NpcCordinator
{
private:
	std::vector<NPCPlayers*> teamPlayers;
	int no_of_alive_players;
	float average_health;
	float average_ammo;
public:
	NpcCordinator();
	void addNewPlayer(NPCPlayers* m_newPlayer);
	~NpcCordinator();
};*/
#endif