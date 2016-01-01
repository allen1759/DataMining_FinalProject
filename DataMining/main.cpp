//
//  main.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Function.h"
#include "Attribute.h"
#include "Data.h"
#include "Tree.h"
#include "Evaluation.h"
using namespace std;

int main(int argc, const char * argv[])
{
    srand ( unsigned ( time(0) ) );
    string attrDirect = "/Users/Allen/Documents/workspace/DataMining/attributes.txt";
    string dataDirect = "/Users/Allen/Documents/workspace/DataMining/expanded.txt";
    string outputDirect = "/Users/Allen/Documents/workspace/DataMining/record-1500-GINI.txt";
    
    int times = 100, trainingSize = 1500;
    Attribute attrs;
    vector<Data> allData, trainingData, testingData;
    fstream out(outputDirect, ios::out);
    Print2FileAttrs(out);
    
    for(int t=0; t<times; t+=1) {
        DecisionTree myDecisionTree(0.8);
        SplitMethod method = GINI;
        Evaluation evaluation;
        
        PreProcess(attrDirect, attrs, dataDirect, allData, trainingSize, trainingData, testingData);
        TrainingStep(myDecisionTree, trainingData, attrs, method, evaluation, false);
        
        TestingStep(myDecisionTree, testingData, evaluation, false);
        Print2File(out, trainingData, testingData, evaluation);
    }
    
    return 0;
}
