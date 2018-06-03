#include <iostream>
#include <vector>



#include "Net.h"
#include <cstdlib>

#ifndef TEST_CPP
#define TEST_CPP


using namespace std;


int main(){
    
    vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(2);
    topology.push_back(1);
    
    Net myNet(topology);
    
    
    
  for ( unsigned int i = 0; i < 10000; ++i){
      
    vector<double> inputVals;
    vector<double> targetVals;
    vector<double> resultsVals;
    
    int x = rand() % 2;
    int y = rand() % 2;
    
    int ActualValue =  x xor y;
    
    cout << "Input values: " << x << " " << y << endl;
    cout << "Target value: " << ActualValue << endl;
    
    
    
    inputVals.push_back(x);
    inputVals.push_back(y);
    
    targetVals.push_back(ActualValue);
    
    
    
    myNet.feedForward(inputVals);
    
    
    
    myNet.backProp(targetVals);
    
    
    myNet.getResults(resultsVals);
    cout << "Calculated value(s): ";
    cout << resultsVals.at(0) << endl;
    
    inputVals.clear();
    targetVals.clear();
    
    
    }
    
    
    
}



#endif
