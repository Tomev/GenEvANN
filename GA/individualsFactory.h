#ifndef GENEVANN_INDIVIDUALSFACTORY_H
#define GENEVANN_INDIVIDUALSFACTORY_H


#include "../NN/neuralNet.h"
#include "individual.h"
#include "Strategies/strategies.h"

class individualsFactory
{
public:

  individualsFactory(neuralNet* nn, i_distribution* distribution);

  individual createIndividual();
  individual createIndividual(individual* p1, individual* p2);

private:
  i_distribution* distribution = NULL;
  neuralNet* nn = NULL;
  unsigned int individualStrategyId = 0;

  individual createNeuralIndividual();
  individual createRSSBounceIndividual();
  individual createRSSRollIndividual();

};


#endif //GENEVANN_INDIVIDUALSFACTORY_H
