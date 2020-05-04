#include "source/AI.cpp"

int main(int argc, char const *argv[])
{
	printf("enter health ");
	float health;
	std::cin>>health;
	printf("enter ammo");
	float ammo;
	std::cin>>ammo;
	printf("enter distance ");
	float distance;
	std::cin>>distance;

	printf("the inputs are health(%f), ammo(%f), distance(%f)\n",health, ammo, distance );

	NPCPlayers* npcplayer = new NPCPlayers();

	npcplayer->setHealth(health);
	npcplayer->setAmmo(ammo);
	npcplayer->setDistance(distance);

	npcplayer->actionSelection();

/*
	FuzzyMembershipFunc* fuzzyMembership = new FuzzyMembershipFunc();

	float attack_level = fuzzyMembership->calcAttackLevel(health,ammo,distance);

	std::string action= fuzzyMembership->calcAction(attack_level);

	std::cout<<"the fuzzy choosen action is : "<< action <<std::endl;*/

	return 0;


}