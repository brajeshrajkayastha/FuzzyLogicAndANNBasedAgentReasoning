#include "include/fuzzy.hpp"	

Fuzzy::Fuzzy(){

	//Membership function construction for health
	printf("initializing Fuzzy Logic membership function construction...\n");

	healthMF[0] = new MF_Trapezoid();
	
	healthMF[0]->setName("low_health");
	healthMF[0]->setInterval(-1,30);
	healthMF[0]->setMiddle(0,20);

	healthMF[1] = new MF_Trapezoid;

	healthMF[1]->setName("mid_health");
	healthMF[1]->setInterval(20,80);
	healthMF[1]->setMiddle(35,65);

	healthMF[2] = new MF_Trapezoid;

	healthMF[2]->setName("high_health");
	healthMF[2]->setInterval(70,101);
	healthMF[2]->setMiddle(85,101);

	printf("Health membership function constructed.\n");

	//Membership function construction for ammo

	ammoMF[0]= new MF_Trapezoid;

	ammoMF[0]->setName("low_ammo");
	ammoMF[0]->setInterval(-1,25);
	ammoMF[0]->setMiddle(0,15);

	ammoMF[1]= new MF_Triangle;

	ammoMF[1]->setName("mid_ammo");
	ammoMF[1]->setInterval(20,80);
	ammoMF[1]->setMiddle(50,50);
	
	ammoMF[2]= new MF_Trapezoid;

	ammoMF[2]->setName("high_ammo");
	ammoMF[2]->setInterval(75,101);
	ammoMF[2]->setMiddle(85,101);

	printf("Ammo membership function constructed.\n");

	//Membership function construction for distance

	distanceMF[0]= new MF_Trapezoid;

	distanceMF[0]->setName("dist_very_near");
	distanceMF[0]->setInterval(0,10);
	distanceMF[0]->setMiddle(0,7);

	distanceMF[1]= new MF_Triangle;

	distanceMF[1]->setName("dist_near");
	distanceMF[1]->setInterval(5,30);
	distanceMF[1]->setMiddle(11,11);

	distanceMF[2]= new MF_Trapezoid;

	distanceMF[2]->setName("dist_mid");
	distanceMF[2]->setInterval(20,80);
	distanceMF[2]->setMiddle(40,60);
	
	distanceMF[3]= new MF_Triangle;

	distanceMF[3]->setName("dist_far");
	distanceMF[3]->setInterval(70,100);
	distanceMF[3]->setMiddle(85,85);

	distanceMF[4]= new MF_Trapezoid;

	distanceMF[4]->setName("dist_very_far");
	distanceMF[4]->setInterval(90,110);
	distanceMF[4]->setMiddle(100,110);

	printf("Distance membership function constructed.\n");

	//Membership function construction for action

	actionMF.push_back(new MF_Trapezoid);

	actionMF.at(0)->setName("runaway");
	actionMF.at(0)->setInterval(0,25);
	actionMF.at(0)->setMiddle(0,15);

	actionMF.push_back(new MF_Triangle);

	actionMF.at(1)->setName("idle");
	actionMF.at(1)->setInterval(10,35);
	actionMF.at(1)->setMiddle(25,25);

	actionMF.push_back(new MF_Triangle);

	actionMF.at(2)->setName("defensive");
	actionMF.at(2)->setInterval(25,70);
	actionMF.at(2)->setMiddle(37,37);

	actionMF.push_back(new MF_Triangle);

	actionMF.at(3)->setName("low_attack");
	actionMF.at(3)->setInterval(50,80);
	actionMF.at(3)->setMiddle(65,65);

	actionMF.push_back(new MF_Trapezoid);

	actionMF.at(4)->setName("high_attack");
	actionMF.at(4)->setInterval(75,100);
	actionMF.at(4)->setMiddle(85,100);

	printf("Action membership function constructed.\n");

	/*  initalizing ruleBase action reference.
		&action_mode_values.at(2) reference to defence defuzzy value
		&action_mode_values.at(1) reference to normal defuzzy value
		&action_mode_values.at(0) reference to attack defuzzy value
	*/

	printf("initializing rule base...\n");
	ruleBase[0][0][0] = &action_mode_values.at(2);
	ruleBase[0][0][1] = &action_mode_values.at(2);
	ruleBase[0][0][2] = &action_mode_values.at(2);
	ruleBase[0][1][0] = &action_mode_values.at(2);
	ruleBase[0][1][1] = &action_mode_values.at(1);
	ruleBase[0][1][2] = &action_mode_values.at(1);
	ruleBase[0][2][0] = &action_mode_values.at(2);
	ruleBase[0][2][1] = &action_mode_values.at(1);
	ruleBase[0][2][2] = &action_mode_values.at(0);
	ruleBase[1][0][0] = &action_mode_values.at(2);
	ruleBase[1][0][1] = &action_mode_values.at(2);
	ruleBase[1][0][2] = &action_mode_values.at(2);
	ruleBase[1][1][0] = &action_mode_values.at(2);
	ruleBase[1][1][1] = &action_mode_values.at(1);
	ruleBase[1][1][2] = &action_mode_values.at(1);
	ruleBase[1][2][0] = &action_mode_values.at(2);
	ruleBase[1][2][1] = &action_mode_values.at(1);
	ruleBase[1][2][2] = &action_mode_values.at(0);
	ruleBase[2][0][0] = &action_mode_values.at(1);
	ruleBase[2][0][1] = &action_mode_values.at(1);
	ruleBase[2][0][2] = &action_mode_values.at(0);
	ruleBase[2][1][0] = &action_mode_values.at(1);
	ruleBase[2][1][1] = &action_mode_values.at(0);
	ruleBase[2][1][2] = &action_mode_values.at(0);
	ruleBase[2][2][0] = &action_mode_values.at(1);
	ruleBase[2][2][1] = &action_mode_values.at(0);
	ruleBase[2][2][2] = &action_mode_values.at(0);
	ruleBase[3][0][0] = &action_mode_values.at(1);
	ruleBase[3][0][1] = &action_mode_values.at(0);
	ruleBase[3][0][2] = &action_mode_values.at(0);
	ruleBase[3][1][0] = &action_mode_values.at(0);
	ruleBase[3][1][1] = &action_mode_values.at(0);
	ruleBase[3][1][2] = &action_mode_values.at(0);
	ruleBase[3][2][0] = &action_mode_values.at(0);
	ruleBase[3][2][1] = &action_mode_values.at(0);
	ruleBase[3][2][2] = &action_mode_values.at(0);
	ruleBase[4][0][0] = &action_mode_values.at(1);
	ruleBase[4][0][1] = &action_mode_values.at(0);
	ruleBase[4][0][2] = &action_mode_values.at(0);
	ruleBase[4][1][0] = &action_mode_values.at(0);
	ruleBase[4][1][1] = &action_mode_values.at(0);
	ruleBase[4][1][2] = &action_mode_values.at(0);
	ruleBase[4][2][0] = &action_mode_values.at(0);
	ruleBase[4][2][1] = &action_mode_values.at(0);
	ruleBase[4][2][2] = &action_mode_values.at(0);
	// printf("initialized rule base\n");

}

std::vector<float> Fuzzy::calcNNInputs(float m_health, float m_ammo, float m_distance ){

	// printf("health(%f), ammo(%f), distance(%f) \n",m_health, m_ammo, m_distance );

/*	printf("\n health \n");

	for (int i = 0; i < 3; ++i)
	{
		float health = healthMF[i]->getValue(m_health);
		printf("mem_val: %f with %s\n",health, healthMF[i]->getName());
	}

	printf("\n ammo \n");

	for (int i = 0; i < 3; ++i)
	{
		float ammo = ammoMF[i]->getValue(m_ammo);
		printf("mem_val: %f with %s\n", ammo, ammoMF[i]->getName());

	}

	printf("\n distance \n");

	for (int i = 0; i < 5; ++i)
	{
		float dist = distanceMF[i]->getValue(m_distance);
		printf("mem_val: %f with %s\n",dist, distanceMF[i]->getName());

	}

*/

	//Calculating the membership values for all the fuzzy set rules

	printf("calculating membership values for all fuzzy set rules..\n\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{	
				float health = 0.0f;
				float ammo = 0.0f;
				float distance = 0.0f;

				health = healthMF[k]->getValue(m_health);
				ammo = ammoMF[j]->getValue(m_ammo);
				distance = distanceMF[i]->getValue(m_distance);


				if(health <= 0 || ammo <= 0 || distance <= 0){
					continue;
				}

				printf("The fuzzy rule at (%i,%i,%i) with values: %s(%f) ^ %s(%f) ^ %s(%f) is activated\n ",k,j,i,healthMF[k]->getName(),health,ammoMF[j]->getName(),ammo,distanceMF[i]->getName(),distance);

/*				printf("(%i) health membership value: %f with %s\n",k, health, healthMF[k]->getName());
				printf("(%i) ammo membership value: %f with %s\n",j, ammo,ammoMF[j]->getName());
				printf("(%i) distance membership value: %f with %s\n ",i,distance, distanceMF[i]->getName());*/
				
				float fuzzy_value = 0.0f;

				//fuzzy set ^ operation
				fuzzy_value = ((health <= ammo && health <= distance)? health : ((ammo <= health && ammo <= distance)?ammo:((distance <= health && distance <= ammo)?distance:0.0f)));
				// fuzzy_value = (ammo <= health && ammo <= distance)? ammo : 0.0f;	
				// fuzzy_value = (distance <= health && distance <= ammo)? distance : 0.0f;	

				printf("Fuzzy set operation value for the rule is: %f\n\n", fuzzy_value);

				//mapping ruleBase and updating the defuzzification values
				if(*ruleBase[i][j][k] > 0){
					float temp = *ruleBase[i][j][k];
					*ruleBase[i][j][k] = (temp+fuzzy_value)/2;
				}else{
					*ruleBase[i][j][k] = fuzzy_value;
				}

			}
		}
	}

	printf("Input values for the ANN: attack (%f), normal (%f) and defence (%f)\n",action_mode_values.at(0), action_mode_values.at(1), action_mode_values.at(2));	
	return action_mode_values;
	//printf("Action mode values; attack (%f) normal (%f) defence (%f) \n",action_mode_values.at(0), action_mode_values.at(1), action_mode_values.at(2));


/*	float a1 = action_mode_values.at(2)*(0.5f*8.3f+25); //Area of defence
	float a2 = action_mode_values.at(1)*25; // Area of normal
	float a3 = action_mode_values.at(0)*(0.5f*8.7f+25); //Area of attack

	float x1 = 2*(((action_mode_values.at(2)+25)/2)+((2*action_mode_values.at(2)+8.3)/3)); // centriod of defence
	float x2 = 2*((2*action_mode_values.at(1)+25)/3); // centriod of normal
	float x3 = 2*(((action_mode_values.at(0)+25)/2)+((2*action_mode_values.at(0)+8.7)/3)); // centriod of attack

	float defuzzified_value  = ((a1*x1)+(a2*x2)+(a3*x3))/(a1+a2+a3); //defuzzified value of the Attack Level Set*/
	
	/*float defuzzified_value = (attack_defuzz_defense_interval*action_mode_values.at(2)+attack_defuzz_normal_interval*action_mode_values.at(1)+attack_defuzz_attack_interval*action_mode_values.at(0))/(action_mode_values.at(0)+action_mode_values.at(1)+action_mode_values.at(2));	

	printf("the defuzzified_value value : %f\n",defuzzified_value );
	return defuzzified_value;*/

}

/*std::string Fuzzy::calcAction(float attackLevel){

	printf("The attack level value : %f \n", attackLevel);
	
	float prev_val = 0.0f;
	int action_index = -1;
	std::string action_name = "";

	for (int i = 0; i < 5; ++i)
	{
		float action_fuzzy_value = 0.0f;

		action_fuzzy_value = actionMF[i]->getValue(attackLevel);

		printf("(%i)action fuzzy value : %f with %s\n",i,action_fuzzy_value, actionMF[i]->getName());

		if(action_fuzzy_value >= prev_val){
			printf("prev action value %f\n",prev_val);
			prev_val = action_fuzzy_value;
			action_index = i;
		}
	}

	// printf("the chosen action is %s\n", actionMF[action_index]->getName());

	action_name = actionMF[action_index]->getName();
	return action_name;

}*/