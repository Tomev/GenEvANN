#ifndef GENEVANN_NEURALNET_H
#define GENEVANN_NEURALNET_H

#include "neuron.h"
#include "../FA/Strategies/neuralFireflyStrategy.h"

// TODO: constant correctness

class neuralNet {
public:
  neuralNet(vector<unsigned int> *topology);

	void setInputsValue(const vector<double> *inputs);
	void setWeightsFromNeuronsStructure(const vector<neuralFireflyStrategy::layer>* solution);
	void feedForward();
	void resetNonInputLayerInputs();
  void getResults(vector<double> *results);

	double getNeuronsBias(unsigned int layerNo, unsigned int neuronNo);
	double getNeuronsIthOutputWeight(unsigned int layerNo, unsigned int neuronNo, unsigned int i);


  vector<unsigned int>* getTopology();

	string toString();
  void print();

protected:

private:
  vector<layer> net;
  vector<unsigned int> *topology;
  void setNeuronConnections();
};

#endif //GENEVANN_NEURALNET_H
