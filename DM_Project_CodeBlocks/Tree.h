//
//  Tree.h
//  DataMining
//
//  Created by 楊智偉 on 12/30/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include <vector>
#include "Node.h"
#include "Data.h"
#include "Attribute.h"

enum SplitMethod
{
    GINI=0,
    ENTROPY=1,
    ERROR=2
};

class DecisionTree
{
private:
    typedef double (DecisionTree::*splitPtr)(std::vector< std::vector<Data> > & currSplitData);
    
    Node * head = nullptr;
    double purityThreshold = 0.8;
    int cntNodes = 0;
    int maxLevel = 0;
    const int MethodSize = 3;
    // std::vector< splitPtr > methods;
    std::vector< double (DecisionTree::*)(std::vector< std::vector<Data> > &) > methods;
    
    double SplitByGini(std::vector< std::vector<Data> > & currSplitData);
    double SplitByEntropy(std::vector< std::vector<Data> > & currSplitData);
    double SplitByError(std::vector< std::vector<Data> > & currSplitData);
    
    int GetMinSplit(const std::vector<Data> & datas, std::vector< std::vector<Data> > & splitedData, const Attribute & attrs, SplitMethod whichMethod);
    double getPurity(const std::vector<Data> & arr);
    void printSpace(int n) const;
    Node * ConstructDecisionTreeHelp(std::vector<Data> & allData, const Attribute & attrs, int level, SplitMethod whichMethod);
    bool PredictFromNode(Node * ptr, Data & currData);
    void PrintNode(Node * curr, int level);
    
public:
    DecisionTree();
    DecisionTree(double thres);
    void ConstructDecisionTree(std::vector<Data> & allData, const Attribute & attrs, SplitMethod whichMethod);
    bool PredictData(Data & currData);
    void Print();
};

#endif /* Tree_h */
