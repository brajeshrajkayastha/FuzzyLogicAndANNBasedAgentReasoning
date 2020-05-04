#include "include/neuralnet.hpp"

NeuralNetwork::NeuralNetwork(Fuzzy* m_fuzzyMF){
	srand (time(NULL));

	this->fuzzy = m_fuzzyMF;
}

void NeuralNetwork::createLayer(int no_of_neuron,int no_of_weight,std::vector<std::vector<float>>weight_values, std::string layer_name, std::vector<FuzzyFunction*>* m_MF){

	// printf("constructing the network layer with nodes %i ...\n",no_of_neuron );

	Layer* m_layer = new Layer(m_MF);
	for (int i = 0; i < no_of_neuron; ++i)
	{
		// printf("constructing the neuron...\n",no_of_neuron );


		Neuron* m_neuron = new Neuron(no_of_weight, weight_values.at(i));
		m_layer->addNeurons(m_neuron);
	}

	m_layer->setName(layer_name);
	network.push_back(m_layer);
}


void NeuralNetwork::initalizeInputLayer(std::vector<float> m_inputs){
	printf("initializing the input layer...\n");
	for (int i = 0; i < (network.at(0)->getNeurons()).size(); ++i)
	{
		network.at(0)->getNeurons().at(i)->setInput(m_inputs.at(i));
	}
}

void NeuralNetwork::forwardPropagate(){
	printf("starting forward propagation...\n");

	network.at(0)->feedForward(nullptr);
	network.at(1)->feedForward(network.at(0));

/*	for (int i = 0; i < network.size(); ++i)
	{
		network.at(i)->feedForward(network.at(i-1));
	}*/
}

NeuralNetwork::Layer::Layer(std::vector<FuzzyFunction*>* m_MF){
	this->my_MF = m_MF;
}
void NeuralNetwork::Layer::addNeurons(NeuralNetwork::Neuron* m_neuron){
	this->neurons.push_back(m_neuron);
}

std::vector<NeuralNetwork::Neuron*> NeuralNetwork::Layer::getNeurons(){
	return this->neurons;
}

void NeuralNetwork::Layer::setName(std::string m_name){
	this->layer_name = m_name;
}

std::string NeuralNetwork::Layer::getName(){
	return this->layer_name;
}

void NeuralNetwork::Layer::setOutput(float m_output){
	this->layer_output = m_output;
}

float NeuralNetwork::Layer::getOutput(){
	return this->layer_output;
}

void NeuralNetwork::Layer::feedForward(Layer* prevLayer = nullptr){
	if(this->layer_name == "centriod"){
		for (int i = 0; i < this->neurons.size(); ++i)
		{	
			if(prevLayer == nullptr){
				this->neurons.at(i)->calculateOutput();
			}else{
				this->neurons.at(i)->setInput(prevLayer->getOutput());
				this->neurons.at(i)->calculateOutput();
			}
			// float neuron_output = this->neurons.at(i)->getOutputValue();
		}
		printf("calculating weighted average function...\n");
		centriodTransferFunction(this);
		//this->setOutput(); 

	}else if (this->layer_name == "comparator"){
		for (int i = 0; i < this->neurons.size(); ++i)
		{
			if(prevLayer == nullptr){
				this->neurons.at(i)->calculateOutput(this->my_MF->at(i));
			}else{
				this->neurons.at(i)->setInput(prevLayer->getOutput());
				this->neurons.at(i)->calculateOutput(this->my_MF->at(i));

				//printf("the actionMF is %s with %f\n",my_MF->at(i)->getName(), );
			}
			// float neuron_output = this->neurons.at(i)->getOutputValue();
		}
		comparatorFunction(this);
		//this->setOutput(); 
	}
}

/*NeuralNetwork::Neuron::Neuron(int no_of_weight){
	this->createWeights(no_of_weight);
}*/

NeuralNetwork::Neuron::Neuron(int no_of_weight, std::vector<float> weight_values){
	this->createWeights(no_of_weight, weight_values);
}

/*void NeuralNetwork::Neuron::createWeights(int no_of_weight)
{
	for (int i = 0; i < no_of_weight+1; ++i)
	{
		Connection* conn;
		conn.weight = setRandomWeight();
		weights.push_back(conn);
	}
}*/

void NeuralNetwork::Neuron::createWeights(int no_of_weight, std::vector<float> weight_values)
{
	for (int i = 0; i < no_of_weight; ++i)
	{
		Connection* conn = new Connection;
		conn->weight = weight_values.at(i);
		weights.push_back(conn);
	}
}

/*void NeuralNetwork::Neuron::setRandomWeight(){
	return float(rand() % 10 + 1);
}*/

void NeuralNetwork::Neuron::setInput(float m_input)
{
	this->input_value = m_input;
}

void NeuralNetwork::Neuron::updateDeltaWeight(float m_delta_weight)
{

	this->weights.at(0)->delta_weight = m_delta_weight;
	this->weights.at(0)->updateWeight();
} 

void NeuralNetwork::Neuron::updateDeltaWeight(std::vector<float> m_delta_weights)
{	
	for (int i = 0; i < weights.size(); ++i)
	{
		this->weights.at(i)->delta_weight = m_delta_weights.at(i);
		this->weights.at(i)->updateWeight();
	}
} 

void NeuralNetwork::Neuron::calculateOutput()
{
	this->output_value = input_value*weights.at(0)->weight;
}

void NeuralNetwork::Neuron::calculateOutput(FuzzyFunction* m_fuzzyMF)
{	
	if(this->weights.size() <= 1 || this->weights.size() >3){
		return;
	}

	if(! m_fuzzyMF){
		output_value = 0;
		return;
	}

	m_fuzzyMF->setInterval(weights.at(0)->weight,weights.at(1)->weight);
	float mid_value = (weights.at(0)->weight + weights.at(1)->weight)/2;
	m_fuzzyMF->setMiddle(mid_value,mid_value);
	output_value = m_fuzzyMF->getValue(input_value);

	printf("output value %s with %f\n",m_fuzzyMF->getName(), output_value);
}


/*std::vector<float> NeuralNetwork::Neuron:: getWeight()
{
	std::vector<float> m_weights;
	for (int i = 0; i < this->weights.size(); ++i)
	{
		m_weights.push_back(this->weights.at(i)->weight);
	}

	return m_weights;
}*/

/*void NeuralNetwork::Neuron::feedForward(){

}*/

float NeuralNetwork::Neuron::getOutputValue(){
	return this->output_value;
}

float NeuralNetwork::Neuron::getInputValue(){
	return this->input_value;
}

void NeuralNetwork::Layer::centriodTransferFunction(Layer* m_nnLayer){
	float summed_output = 0.0f;
	float summed_input = 0.0f;
	for (int i = 0; i < m_nnLayer->getNeurons().size(); ++i)
	{
		summed_output += m_nnLayer->getNeurons().at(i)->getOutputValue();
		summed_input += m_nnLayer->getNeurons().at(i)->getInputValue();
	}

	float output = summed_output/summed_input;
	printf("weighted average function output:  %f\n",output);
	m_nnLayer->setOutput(output);


}

void NeuralNetwork::Layer::comparatorFunction(Layer* m_nnLayer){

	int index = -1;
	float prev_value = -1;
	for (int i = 0; i < m_nnLayer->getNeurons().size(); ++i)
	{
		float neuron_output = m_nnLayer->getNeurons().at(i)->getOutputValue();
		if(neuron_output > prev_value){
			// printf("the prev_value %f\n",prev_value );
			
			prev_value = neuron_output;
			index = i;
		}
	}
	 m_nnLayer->setOutput(float(index));
}

void NeuralNetwork::feedback(float delta_value, int index){
	/*Neuron* neuron = network.at(1)->getNeurons().at(index);

	std::vector<float> delta_weights;

	delta_weights = neuron.getWeights*/
}