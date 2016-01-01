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
    
    int trainingSize = 15;
    Attribute attrs;
    vector<Data> allData, trainingData, testingData;
    DecisionTree myDecisionTree(0.8);
    SplitMethod method = ENTROPY;
    
    PreProcess(attrDirect, attrs, dataDirect, allData, trainingSize, trainingData, testingData);
    TrainingStep(myDecisionTree, trainingData, attrs, method);
    
//     myTree.Print();
    
    
    // ========== using testing dataset ==========
    clock_t start_time, end_time;
    start_time = clock(); /* mircosecond */
    
    Evaluation eval;
    for(auto & data : testingData) {
        bool predicted = myDecisionTree.PredictData(data);
        if( data.canEat && predicted ) {
            eval.setTP( eval.getTP()+1 );
        }
        else if( data.canEat && !predicted ) {
            eval.setFN( eval.getFN()+1 );
        }
        else if( !data.canEat && predicted ) {
            eval.setFP( eval.getFP()+1 );
        }
        else if( !data.canEat && !predicted ) {
            eval.setTN( eval.getTN()+1 );
        }
    }
    
    end_time = clock();
    cout << "           ================ Predicting Step ================" << endl;
    cout << "               Testing dataset size = " << testingData.size() << endl << endl;
    eval.PrintMatrix();
    cout << "               Precict using Time: " << static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC << "(seconds)" << endl << endl;
    // ========== using testing dataset ==========
    
    return 0;
}
