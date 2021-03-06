#include "rssBounceIndividualStrategy.h"

#include <iostream>
#include <cassert>

RSSBounceIndividualStrategy::RSSBounceIndividualStrategy(
    vector<unsigned int> *topology, i_distribution *distribution) : neuralIndividualStrategy(topology, distribution)
{}

void RSSBounceIndividualStrategy::initializeSolution(){
  // For each potential layer
  for(unsigned int l = 0; l < topology->size()-1; ++l)
  {
    // Add new layer to solution
    solution.push_back(layer());

    // For each potential neuron
    for(unsigned int n = 0; n < topology->at(l); ++n)
    {
      // Add new neuron (which is vector of weights) to solution
      solution.at(l).push_back(neuron());

      // For each potential weight + bias
      for(unsigned int w = 0; w < topology->at(l+1) + 1; ++w)
      {
        // Add new weight selected from given distribution to the vector
        solution.at(l).at(n).push_back(reduceToBounds(distribution->getRandomNumberFromDistribution()));
      }
    }
  }
}

void RSSBounceIndividualStrategy::setSolution(void *newSolution)
{
  /* As copying pointer won't do the trick each value in current
   * individuals solution vector is replaced by adequate value from
   * new solution. Note that size of new solution and current solution
   * are meant to be same. */

  vector<layer>* parent = (vector<layer>*) newSolution;

  assert(parent->size() == solution.size());

  // For each layer
  for(unsigned int l = 0; l < solution.size(); ++l)
  {
    assert(parent->at(l).size() == solution.at(l).size());

    // For each neuron on that layer
    for(unsigned int n = 0; n < solution.at(l).size(); ++n)
    {
      assert(parent->at(l).at(n).size() == solution.at(l).at(n).size());

      // For each weight of that neuron
      for(unsigned int w = 0; w < solution.at(l).at(n).size(); ++w)
      {
        // Replace solutions value at current weight
        solution.at(l).at(n).at(w) = reduceToBounds(parent->at(l).at(n).at(w));
      }
    }
  }
}

// This operator selects n non-input nodes of the network which the parent chromosome
// represents. For each of the ingoing links to these n nodes, the operator adds to
// the links weight a random value from the initialization probability i_distribution.
void RSSBounceIndividualStrategy::nodeMutation()
{
  int layerNumber;
  int neuronNumber;

  // For each node to mutate.
  for(unsigned int i = 0; i < numberOfNodesToMutate; ++i)
  {
    // Select random layer and position in the layer.
    layerNumber   = rand() % solution.size();
    neuronNumber  = rand() % solution.at(layerNumber).size();

    // For each weight of selected neuron
    for(unsigned int j = 0; j < solution.at(layerNumber).at(neuronNumber).size(); ++j)
    {
      // Add pseudo-random number generated by selected i_distribution.
      double newSolution = solution[layerNumber][neuronNumber][j] + distribution->getRandomNumberFromDistribution();
      newSolution = reduceToBounds(newSolution);
      solution.at(layerNumber).at(neuronNumber).at(j) = newSolution;
    }
  }
}

// In strategies with RSS this should be called before assigning weight
double RSSBounceIndividualStrategy::reduceToBounds(double val)
{
  //cout << "Value reduction start for value: " << val << endl;

  double reducedValue = val;
  int counter = 0;

  while(reducedValue > _upperBound || reducedValue < _lowerBound){
    if (reducedValue < _lowerBound){
      reducedValue = _lowerBound - (reducedValue - _lowerBound);
    }
    else if (reducedValue > _upperBound){
      reducedValue = _upperBound - (reducedValue - _upperBound);
    }
    ++counter;

    if(counter > 10)
      cout << counter << ": " << reducedValue << endl;

  }

  //cout << "Reduced val: " << reducedValue << endl;

  return reducedValue;
}
