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
    random_shuffle(allData.begin(), allData.end(), RNG());
    int trainingSize = 15;
    vector<Data> trainingData(allData.begin(), allData.begin()+trainingSize);
    vector<Data> testingData(allData.begin()+trainingSize, allData.end());
    // ========== get the traing dataset from file ==========
    
    
    // ========== using traing dataset ==========
    start_time = clock(); /* mircosecond */
    
    DecisionTree myTree(0.8);
    myTree.ConstructDecisionTree(trainingData, attrs, GINI);
    
    end_time = clock();
    cout << "Training dataset size = " << trainingData.size() << endl;
    cout << "Construct DecisionTree Time: " << static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC << endl;
    // ========== using traing dataset ==========
    
//     myTree.Print();
    
    // ========== using testing dataset ==========
    start_time = clock(); /* mircosecond */
    
    Evaluation eval;
//    int cntSucceed = 0;
    for(auto & data : testingData) {
        bool predicted = myTree.PredictData(data);
//        if( data.canEat == myTree.PredictData(data) ) {
//            cntSucceed += 1;
//        }
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
    cout << endl << endl;
    cout << "Testing dataset size = " << testingData.size() << endl;
//    cout << "Number of Correct Predict = " << cntSucceed << endl;
//    cout << "Predict Correct Rate = " << static_cast<double>(cntSucceed) / testingData.size() * 100 << "%" << endl;
    eval.PrintMatrix();
    cout << "Precict using Time: " << static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC << endl;
    // ========== using testing dataset ==========
    
    cout << allData[1].data[1] << endl;
    // cout << "The End" << endl;
    
    return 0;
}
