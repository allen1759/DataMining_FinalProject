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
    clock_t start_time, end_time;
    
    fstream in;
    in.open("/Users/Allen/Documents/workspace/DataMining/attributes.txt", ios::in);
    Attribute attrs;
    attrs.initial(in);
    in.close();
    
    // ========== get the traing dataset from file ==========
    in.open("/Users/Allen/Documents/workspace/DataMining/expanded.txt", ios::in);
    vector<Data> allData;
    InputAllDatas(in, allData, attrs);
    int trainingSize = 15;
    vector<Data> trainingData(allData.begin(), allData.begin()+trainingSize);
    vector<Data> testingData(allData.begin()+trainingSize, allData.end());
    in.close();
    // ========== get the traing dataset from file ==========
    
    
    
    // ========== using traing dataset ==========
    start_time = clock(); /* mircosecond */
    
    DecisionTree myTree(0.8);
//     myTree.ConstructDecisionTree(trainingData, attrs, GINI);
    myTree.ConstructDecisionTree(trainingData, attrs, ENTROPY);
//    myTree.ConstructDecisionTree(trainingData, attrs, ERROR);
    
    end_time = clock();
    cout << "           ================ Training Step ================" << endl;
    cout << "               Training dataset size = " << trainingData.size() << endl;
    cout << "               Construct DecisionTree Time: " << static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC << "(seconds)"  << endl << endl;
    // ========== using traing dataset ==========
    
//     myTree.Print();
    
    
    
    // ========== using testing dataset ==========
    start_time = clock(); /* mircosecond */
    
    Evaluation eval;
    for(auto & data : testingData) {
        bool predicted = myTree.PredictData(data);
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
