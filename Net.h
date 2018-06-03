#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
using namespace std;


#ifndef NET_H
#define NET_H


struct Connection{
  
  double weight;
  double deltaWeight;
  
};
static double Weight(){ return rand()/double(RAND_MAX);}

class Neuron;
typedef vector<Neuron> Layer;


class Neuron{
  
  private:
  
  double M_outputVal;
  
  vector<Connection> M_outputWeights;
  
  double transferFunction(double x);
  double transferFunctionDerivative(double x);
  double M_myIndex;
  double M_gradient;
  
  double eta;
  double alpha;
  
  public:
  Neuron(unsigned numOutputs, unsigned int myIndex);
  void setOutputVal(double val){ M_outputVal = val;}
  double getOutputVal(){return M_outputVal;}
  void calcOutputGradients(double targetVal);
  void calcHiddenGradients(Layer* nextLayer);
  double sumDOW(Layer* nextLayer);
  void updateInputWeights(Layer* prevLayer);
  
  
  void feedForward(Layer* prevLayer){
    
    double sum = 0.0;
    
    for(unsigned int n = 0; n < prevLayer->size(); ++n){
      
      sum += (prevLayer->at(n).getOutputVal()) * 
      prevLayer->at(n).M_outputWeights.at(M_myIndex).weight;
      
    }
    
    M_outputVal = transferFunction(sum);
    
    
  }

  
};



class Net{
    
  public:
  
  Net(vector<unsigned> topology);
  void feedForward(const vector<double> &inputVals);
  void backProp(const vector<double> &TargetVals);
  void getResults(vector<double> &resultsVals);
  
  private:
  
  vector<Layer> M_Layers;
  double M_error;
  double M_recentAverageError;
    
};



#endif