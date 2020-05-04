#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <time.h> 
#include <string.h>

#include "fuzzy.hpp"

#define ETA = 0.3

class NeuralNetwork
{
public:
	NeuralNetwork(Fuzzy* m_fuzzyMF);
	~NeuralNetwork();

private:

	struct Connection
	{
		float weight;
		float delta_weight;

		void updateWeight(){
			weight += delta_weight;
		}
	};

	class Neuron
	{
	public:
		Neuron(int no_of_weight, std::vector<float> weight_values);
		~Neuron();

		void createWeights(int no_of_weight, std::vector<float> weight_values);
		void setInput(float m_input);
		void updateDeltaWeight(std::vector<float> m_delta_weights);
		void updateDeltaWeight(float m_delta_weights);
/*		float getWeight();
		void feedForward();*/
		void calculateOutput();
		void calculateOutput(FuzzyFunction* m_fuzzyMF);
		float getOutputValue();
		float getInputValue();
	private:	
		//void setRandomWeight();

		std::vector<Connection*> weights;

		float input_value;
		float output_value; 
	};

	class Layer
	{	
	public:

		Layer(std::vector<FuzzyFunction*>* m_MF);
		~Layer();

		void addNeurons(Neuron* m_neuron);
		std::vector<Neuron*> getNeurons();
		void setName(std::string m_name);
		std::string getName();
		void feedForward(Layer* prevLayer);
		void setOutput(float);
		float getOutput();
	private:
		void centriodTransferFunction(Layer* m_nnLayer);
		void comparatorFunction(Layer* m_nnLayer);
	private:
		std::vector<FuzzyFunction*>* my_MF;
		std::string layer_name;
		std::vector<Neuron*> neurons;
		float layer_output;

	};

	Fuzzy* fuzzy;



public:
	std::vector<Layer*> network;
	void createLayer(int no_of_neuron,int no_of_weight,std::vector<std::vector<float>>weight_values, std::string layer_name,std::vector<FuzzyFunction*>* m_MF = nullptr);
	void initalizeInputLayer(std::vector<float> m_inputs);
	void forwardPropagate();
	void feedback(float delta_value, int index);
};