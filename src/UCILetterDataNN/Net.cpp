#ifndef NET_CPP
#define NET_CPP

#include "Net.h"




using namespace std;


Net::Net(vector<unsigned> topology){
  
  unsigned numLayers = topology.size();
  for (unsigned int i = 0; i < numLayers; ++i){
    M_Layers.push_back(Layer());
    
    unsigned numOutputs;
    
    if(i == numLayers - 1){
      numOutputs = 0;
    }
    else{
      numOutputs = topology.at(i + 1);
    }
    
    
    
    
    for (unsigned int j = 0; j <= topology.at(i); ++j){
      M_Layers.back().push_back(Neuron(numOutputs, j));
      cout << "Made a neuron" << endl;
    }
    
    M_Layers.back().back().setOutputVal(1.0);
    
  }
  
  
}

void Net::feedForward(const vector<double> &inputVals){
  
  
  cout << inputVals.size() << " " << M_Layers.at(0).size() - 1 << endl;
  
  assert(inputVals.size() == M_Layers.at(0).size() - 1);
  


  
  
  
  for (unsigned int i = 0; i < inputVals.size(); ++i){
    
    
    
    M_Layers.at(0).at(i).setOutputVal(inputVals.at(i));
    
  }
  

  
  for (unsigned int layerNum = 1; layerNum < M_Layers.size(); ++layerNum){
    
    Layer* prevLayer = &( M_Layers.at(layerNum - 1));
    
    
    for(unsigned int j = 0; j < M_Layers.at(layerNum).size() - 1; ++j){
      
 
      
      M_Layers.at(layerNum).at(j).feedForward(prevLayer);
     
    }
    
  }
  
  
  
  
  
}

void Net::backProp(const vector<double> &TargetVals){
  
  Layer* outputLayer = &(M_Layers.back());
  
  M_error = 0.0;
  
  for ( unsigned int n = 0; n < TargetVals.size(); ++n){
    
    double delta = TargetVals.at(n) - outputLayer->at(n).getOutputVal();
    cout << "delta is" << delta << endl;
    
    M_error += pow(delta, 2);
    
    
  }
  
  M_error /= outputLayer->size() - 1;
  
  M_error = sqrt(M_error);
  cout << "After everything loop, merror is " << M_error << endl;

  for (unsigned int n = 0; n < outputLayer->size() - 1; ++n ){
    
    outputLayer->at(n).calcOutputGradients(TargetVals.at(n));
    
  }
  
  for (unsigned int numLayer = M_Layers.size() - 2; numLayer > 0; --numLayer){
    
    Layer* hiddenLayer = &(M_Layers.at(numLayer));
    Layer* nextLayer = &(M_Layers.at(numLayer + 1));
    
    
    for (unsigned int n = 0; n < hiddenLayer->size(); ++n){
      hiddenLayer->at(n).calcHiddenGradients(nextLayer);
    }
    
    
    
  }
  
  
  for (unsigned int numLayer = M_Layers.size() - 1; numLayer > 0; --numLayer){
    
    Layer* layer = &(M_Layers.at(numLayer));
    Layer* prevLayer = &(M_Layers.at(numLayer - 1));
    
    for (unsigned int n = 0; n < layer->size() - 1; ++n){
      layer->at(n).updateInputWeights(prevLayer);
    }
    
  }
  
  
  
  
}



void Net::getResults(vector<double> &resultsVals) {
  
  resultsVals.clear();
  
  
  for ( unsigned int n = 0; n < M_Layers.back().size(); ++n){
    resultsVals.push_back(M_Layers.back().at(n).getOutputVal());
  }
  
  
}





















Neuron::Neuron(unsigned numOutputs, unsigned int myIndex){
  
  for (unsigned int i = 0; i < numOutputs; ++i){
    M_outputWeights.push_back(Connection());
    M_outputWeights.back().weight = Weight();
  }
  
  M_myIndex = myIndex;
  
  eta = 0.485;
  alpha = 0.5;
  
  
}


double Neuron::transferFunction(double x){return tanh(x);}
double Neuron::transferFunctionDerivative(double x){return (1 - (x * x));}

void Neuron::calcOutputGradients(double targetVal){
  
  double delta = targetVal - M_outputVal;
  
  M_gradient = delta + transferFunctionDerivative(M_outputVal);
  
}
double Neuron::sumDOW(Layer* nextLayer){
  
  double sum = 0.0;
  
  for ( unsigned int n = 0; n < nextLayer->size() - 1; ++n){
    sum += M_outputWeights.at(n).weight * nextLayer->at(n).M_gradient;
  }
  
  return sum;
  
}

void Neuron::calcHiddenGradients(Layer* nextLayer){
  
  
  double delta = sumDOW(nextLayer);
  M_gradient = delta * transferFunctionDerivative(M_outputVal);
  
  
}
void Neuron::updateInputWeights(Layer* prevLayer){
  
  
  for (unsigned int n = 0; n < prevLayer->size(); ++n){
    
    Neuron* neuron = &(prevLayer->at(n));
    double oldDeltaWeight = neuron->M_outputWeights.at(M_myIndex).deltaWeight;
    
    double newDeltaWeight = 
    
      (eta * neuron->getOutputVal() * M_gradient)
      
      + alpha
      
      *oldDeltaWeight;
    
      neuron->M_outputWeights.at(M_myIndex).deltaWeight = newDeltaWeight;
      neuron->M_outputWeights.at(M_myIndex).weight += newDeltaWeight;
  }
  
}





#endif