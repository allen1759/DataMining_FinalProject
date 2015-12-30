//
//  Tree.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/30/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Tree.h"
#include <cmath>
#include <numeric>

#include <iostream>
using namespace std;

double DecisionTree::SplitByGini(std::vector< std::vector<Data> > currSplitData )
{
    vector<int> cntEat( currSplitData.size(), 0 );
    vector<int> cntSum( currSplitData.size(), 0 );
    for(int i=0; i<currSplitData.size(); i+=1) {
        cntSum[i] = static_cast<int>( currSplitData[i].size() );
        for(int j=0; j<currSplitData[i].size(); j+=1) {
            if( currSplitData[i][j].canEat )
                cntEat[i] += 1;
        }
    }
    int total = accumulate(cntSum.begin(), cntSum.end(), 0);
    double ret = 0;
    for(int i=0; i<currSplitData.size(); i+=1) {
        double tmp = cntSum[i] / static_cast<double>(total);
        double gini = pow( static_cast<double>(cntEat[i]) / cntSum[i], 2 )
                    + pow( static_cast<double>(cntSum[i] - cntEat[i]) / cntSum[i], 2 );
        ret += tmp * gini;
    }
    return ret;
}

int DecisionTree::GetMinSplit(const std::vector<Data> & datas, std::vector< std::vector<Data> > & splitedData, const Attribute & attrs)
{
    int retSplit = 0;
    double minSplit = 1e9;
    for(int i=0; i<attrs.getAttrSize(); i+=1) {
        vector< vector<Data> > currSplitData(attrs.getOneSize(i));
        for(int j=0; j<datas.size(); j+=1) {
            currSplitData[ datas[j].data[i] ].push_back( datas[j] );
        }
        
        double currSplit = SplitByGini(currSplitData);
        if( minSplit > currSplit ) {
            retSplit = i;
            minSplit = currSplit;
            splitedData = currSplitData;
        }
    }
    return retSplit;
}

double DecisionTree::getPurity(const std::vector<Data> & arr)
{
    int cntEat = 0;
    for( const Data & e : arr ) {
        if( e.canEat )
            cntEat += 1;
    }
    return static_cast<double>(cntEat) / arr.size();
//    return max( static_cast<double>(arr.size() - cntEat) / arr.size() ,
//                static_cast<double>(cntEat) / arr.size() );
}

//DecisionTree::DecisionTree(std::vector<Data> & allData)
//{
//    head = ConstructDecisionTree(allData);
//}

DecisionTree::DecisionTree(double thres)
{
    purityThreshold = thres;
}

Node * DecisionTree::ConstructDecisionTree(std::vector<Data> & allData, const Attribute & attrs)
{
    Node * currNode = new Node();
    double purity = getPurity(allData);
    if( purity >= purityThreshold ){
        currNode->isLeaf = true;
        currNode->canEat = true;
        return currNode;
    }
    if( purity <= (1-purityThreshold) ){
        currNode->isLeaf = true;
        currNode->canEat = false;
        return currNode;
    }
    
    vector< vector<Data> > splitedData;
    int bestSplit = GetMinSplit(allData, splitedData, attrs);
    if( splitedData.size()!=attrs.getOneSize(bestSplit) ) {
        cout << "Something Wrong!!! - ";
        cout << "DecisionTree::ConstructDecisionTree" << endl;
    }
    currNode->child.resize( attrs.getOneSize(bestSplit) );
    for(int i=0; i<currNode->child.size(); i+=1) {
        currNode->child[i] = ConstructDecisionTree(splitedData[i], attrs);
    }
    
    return currNode;
}