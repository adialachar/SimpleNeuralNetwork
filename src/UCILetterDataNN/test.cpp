#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <boost/tokenizer.hpp> //included so that tokenization can occur using boost
#include "Net.h"
#include <cstdlib>
#include <sstream>
#include <string>

#ifndef TEST_CPP
#define TEST_CPP


using namespace std;


int main(){
    
    vector<unsigned> topology;
    topology.push_back(16);
    topology.push_back(20);
    topology.push_back(20);
    topology.push_back(1);
    
    Net myNet(topology);
    vector<double> targetVals;
    vector<double> inputVals;
    vector<double> resultsVals;
    ifstream infile;
    infile.open("UCItrainingData.txt");
    
    if (infile.fail()){
      cout << "Didnt work" << endl;
      
    }
    
    else{
      
      
      
      string s;
      int counter = 10;
      while (counter > 0){
      infile >> s;  
      char letter = s.at(0);
      bool isThisascrewUp = false;
      targetVals.push_back((int)letter);
      // for(unsigned int i = 65; i < 91; ++i){
      //   targetVals.push_back(i);
      // }
      typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
      
      boost::char_separator<char> cnc{"ABCDEFGHIJKLMNOPQRSTUVWXYZ,"};
      tokenizer tok{s, cnc};
      for (const auto &t : tok){
        
        
        // cout << "t is " << t << endl;
        stringstream ss;
        string b;
        ss << t;
        ss >> b;
        
        
        int Number;
        if ( ! (istringstream(b) >> Number) ) {Number = 0;}
        
        
        
        inputVals.push_back(Number);
        isThisascrewUp = false; 
        
        
      }
      
      // for (unsigned int i = 0; i < inputVals.size(); ++i){
      //   cout << inputVals.at(i) << "|";
      // }
      // cout << endl;
      
      // cout << inputVals.size() << endl;
      
      // break;
      
      myNet.feedForward(inputVals);
  
      myNet.backProp(targetVals);
      
      
      
      
          
      cout << "Target value: " << (int)(letter) <<  " " << letter <<  endl;
    
      myNet.getResults(resultsVals);
      cout << "Calculated value(s): ";
      cout << resultsVals.at(0) << endl;
      
      
      
      inputVals.clear();
      targetVals.clear();
      --counter;
      
      
      
        
        
        
        
        
        
        
      }
      
      
      
      
      
      
      
      
      
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  // for ( unsigned int i = 0; i < 10000; ++i){
      
  //   vector<double> inputVals;
  //   vector<double> targetVals;
  //   vector<double> resultsVals;
    
  //   int x = rand() % 2;
  //   int y = rand() % 2;
    
  //   int ActualValue =  x xor y;
    
  //   cout << "Input values: " << x << " " << y << endl;
  //   cout << "Target value: " << ActualValue << endl;
    
    
    
  //   inputVals.push_back(x);
  //   inputVals.push_back(y);
    
  //   targetVals.push_back(ActualValue);
    
    
    
  //   myNet.feedForward(inputVals);
    
    
    
  //   myNet.backProp(targetVals);
    
    
  //   myNet.getResults(resultsVals);
  //   cout << "Calculated value(s): ";
  //   cout << resultsVals.at(0) << endl;
    
  //   inputVals.clear();
  //   targetVals.clear();
    
    
  //   }
    
    
    
}



#endif
