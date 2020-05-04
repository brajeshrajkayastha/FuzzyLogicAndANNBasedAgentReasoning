#ifndef __FUZZY__HPP
#define __FUZZY__HPP

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <string>

class FuzzyFunction
{
protected :
	float vLeft, vRight;
	char*  name;

public:
	FuzzyFunction(){};
	virtual ~FuzzyFunction(){ delete [] name; name=NULL;}

	virtual void setInterval(float l,
	            float r)
	{vLeft=l; vRight=r; 
		// printf("constructing %s with intervals left(%f) and right(%f)...\n",name,vLeft,vRight);
	}

    virtual void setMiddle( float vL=0,float vR=0)=0;

	virtual void setName(const char* n)
	{ 
	  	name = new char[strlen(n)+1];
		strcpy(name,n);
	}

	bool isDotInInterval(float t)
	{
		if((t>=vLeft)&&(t<=vRight)) return true; else return false;
	}

    char* getName()const{ return name; }

	virtual float getValue(float t)=0;

	virtual std::vector<float> getIntervals() = 0;
};

class MF_Triangle : public FuzzyFunction
{
private: 
	float vMiddle;

public:
	void setMiddle(float dL, float dR)
	{
		vMiddle=dL;
	}

	//calculation of fuzzy membership value
	float getValue(float t)
	{
		if(t<=vLeft)
			return 0;
		else if(t<vMiddle)
			return (t-vLeft)/(vMiddle-vLeft);
		else if(t==vMiddle)
			return 1.0;
		else if(t<vRight)
		    return (vRight-t)/(vRight-vMiddle);
		else
			return 0;
	}

	virtual std::vector<float> getIntervals(){
		std::vector<float> intervals;

		intervals.push_back(vLeft);
		intervals.push_back(vMiddle);
		intervals.push_back(vRight);

		return intervals;
	} 

};

class MF_Trapezoid : public FuzzyFunction
{
private:
	float vLeftMiddle, vRightMiddle;

public:
    void setMiddle(float dL, float dR) 
	{
		vLeftMiddle=dL; vRightMiddle=dR;
	}

	//calculation of fuzzy membership value
	float getValue(float t)
	{
		if(t<=vLeft)
	       return 0;
		else if(t<vLeftMiddle)
			return (t-vLeft)/(vLeftMiddle-vLeft);
		else if(t<=vRightMiddle)
			return 1.0;
		else if(t<vRight)
			return (vRight-t)/(vRight-vRightMiddle);
		else 
		    return 0;
	}  

	virtual std::vector<float> getIntervals(){
		std::vector<float> intervals;

		intervals.push_back(vLeft);
		intervals.push_back(vLeftMiddle);
		intervals.push_back(vRightMiddle);
		intervals.push_back(vRight);

		return intervals;
	} 
};

/*class MF_Half_Trap_Right : public FuzzyFunction
{
private:
	float vMiddle;

public:
    void setMiddle(float dL, float dR) 
	{
		vMiddle=dR;
	}

	float getValue(float t)
	{
		if(t>=vRight)
	       return 0;
		else if(t<=vRight && t>= vMiddle)
			return 1.0;
		else if(t<=vMiddle && t>= vLeft)
			return (t-vLeft)/(vMiddle-vLeft);
		else 
		    return 0;
	}   

	float* getIntervals(){
		static float intervals[3];

		intervals[0] = vLeft;
		intervals[1] = vMiddle;
		intervals[2] = vRight;

		return intervals;
	}
};

class MF_Half_Trap_Left : public FuzzyFunction
{
private:
	float vMiddle;

public:
    void setMiddle(float dL, float dR) 
	{
		vMiddle=dL;
	}

	float getValue(float t)
	{
		if(t<=vLeft)
	       return 0;
		else if(t>=vLeft && t<=vMiddle)
			return 1.0;
		else if(t>=vMiddle && t>=vRight)
			return (vRight-t)/(vRight-vMiddle);
		else 
		    return 0;
	}   

	float* getIntervals(){
		static float intervals[3];

		intervals[0] = vLeft;
		intervals[1] = vMiddle;
		intervals[2] = vRight;

		return intervals;
	}
};*/

class Fuzzy
{
public:
	Fuzzy();
	~Fuzzy();


	//initialization of defuzzification MF intervals for the Weighted Average Method
	float attack_defuzz_defence_interval = 18.0f;
	float attack_defuzz_normal_interval = 50.0f;
	float attack_defuzz_attack_interval = 80.0f;


	//calculating the crisp value(attack_level) for action membership function
	// float calcAttackLevel(float health, float ammo, float distance );
	std::vector<float> calcNNInputs(float health, float ammo, float distance );

	//choosing the action from the action Mf
	std::string calcAction(float attackLevel);

	std::vector<FuzzyFunction*> actionMF;
private:

	//membership functions
	FuzzyFunction *healthMF[3]; //trapeziod,trapeziod,trapeziod MFs
	FuzzyFunction *ammoMF[3]; //trapeziod,triangle,trapeziod MFs
	FuzzyFunction *distanceMF[5]; //trapeziod,triangle,triangle,triangle,trapeziod MFs

	 //trapeziod,triangle,triangle,triangle,trapeziod MFs

	//fuzzy membership values for the defuzzification
	std::vector<float> action_mode_values = {0.0f,0.0f,0.0f}; //attack(value), normal(value), defence(value)

	//fuzzy set rules for all the combinations of the MFs upon ^ operation
	float* ruleBase[5][3][3]; //{distance, ammo, health}

};
#endif