#include "include/AI.hpp"

NPCPlayers::NPCPlayers(){
	this->fuzzy = new Fuzzy();
	this->neuralnet = new NeuralNetwork(fuzzy);

	std::vector<std::vector<float>> layer1_weights = {{fuzzy->attack_defuzz_attack_interval},{fuzzy->attack_defuzz_normal_interval},{fuzzy->attack_defuzz_defence_interval}};
	this->neuralnet->createLayer(3,1,layer1_weights, "centriod");

	std::vector<std::vector<float>> layer2_weights;

	for (int i = 0; i < 5; ++i)
	{
		std::vector<float> intervals;
		std::vector<float> fuzzyInterval = fuzzy->actionMF.at(i)->getIntervals();
		intervals.push_back(fuzzyInterval.at(0));
		intervals.push_back(fuzzyInterval.at(fuzzyInterval.size()-1));

		layer2_weights.push_back(intervals);
	}

	this->neuralnet->createLayer(5,2,layer2_weights, "comparator", &fuzzy->actionMF);

}

void NPCPlayers::setHealth(float m_health){
	this->health = m_health;
}

void NPCPlayers::setAmmo(float m_ammo){
	this->ammo = m_ammo;
}

void NPCPlayers::setDistance(float m_distance){
	this->distance_to_player = m_distance;
}

void NPCPlayers::actionSelection(){

	neuralnet->initalizeInputLayer(fuzzy->calcNNInputs(health, ammo, distance_to_player));

	neuralnet->forwardPropagate();

	int action_index = (int)neuralnet->network.at(neuralnet->network.size()-1)->getOutput();

	printf("the action index is %i \n",action_index+1 );
}
