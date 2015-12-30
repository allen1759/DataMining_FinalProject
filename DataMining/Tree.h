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

class DecisionTree
{
private:
    Node * head = nullptr;
    double purityThreshold = 0.8;
    
    double SplitByGini(std::vector< std::vector<Data> > currSplitData);
    int GetMinSplit(const std::vector<Data> & datas, std::vector< std::vector<Data> > & splitedData, const Attribute & attrs);
    // int GetMinSplit(std::vector<Data> & datas, const Attribute & attrs);
    double getPurity(const std::vector<Data> & arr);
    
public:
    DecisionTree() = default;
    DecisionTree(double thres);
    // DecisionTree(std::vector<Data> & allData);
    Node * ConstructDecisionTree(std::vector<Data> & allData, const Attribute & attrs);
};

#endif /* Tree_h */
