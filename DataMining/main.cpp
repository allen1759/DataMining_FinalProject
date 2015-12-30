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
#include <algorithm>
#include "Function.h"
#include "Attribute.h"
#include "Data.h"
#include "Tree.h"
using namespace std;

int main(int argc, const char * argv[])
{
    fstream in;
    in.open("/Users/Allen/Documents/workspace/DataMining/attributes.txt", ios::in);
    Attribute attrs;
    attrs.initial(in);
    in.close();
    
    in.open("/Users/Allen/Documents/workspace/DataMining/expanded.txt", ios::in);
    vector<Data> allData;
    InputAllDatas(in, allData, attrs);
    random_shuffle(allData.begin(), allData.end());
    int trainingSize = 30;
    vector<Data> trainingData(allData.begin(), allData.begin()+trainingSize);
    vector<Data> testingData(allData.begin()+trainingSize, allData.end());
    cout << "Finish pre-process" << endl;
    
    DecisionTree myTree(0.8);
    myTree.ConstructDecisionTree(trainingData, attrs, 0);
    
    cout << "Hello, World!\n";
    
    return 0;
}
