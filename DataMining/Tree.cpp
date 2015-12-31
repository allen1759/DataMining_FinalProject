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
        // divided by zero case
        if (cntSum[i]==0) {
            continue;
        }
        double tmp = cntSum[i] / static_cast<double>(total);
        double gini = pow( static_cast<double>(cntEat[i]) / cntSum[i], 2 )
                    + pow( static_cast<double>(cntSum[i] - cntEat[i]) / cntSum[i], 2 );
        gini = 1-gini;
        ret += tmp * gini;
    }
    return ret;
}

int DecisionTree::GetMinSplit(const std::vector<Data> & datas, std::vector< std::vector<Data> > & splitedData, const Attribute & attrs)
{
    int retSplit = 0;
    double minSplit = 1e9;
    for(int i=0; i<attrs.getAttrSize(); i+=1) {
        vector< vector<Data> > currSplitData(attrs.getOneSize(i)+1);
        for(int j=0; j<datas.size(); j+=1) {
            if( datas[j].data[i]==0 ) {
                // the case of ? value
            }
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

void DecisionTree::printSpace(int n) const
{
    for(int i=0; i<n; i+=1)
        std::cout << "  ";
}




//DecisionTree::DecisionTree(std::vector<Data> & allData)
//{
//    head = ConstructDecisionTree(allData);
//}

DecisionTree::DecisionTree(double thres)
{
    purityThreshold = thres;
}

Node * DecisionTree::ConstructDecisionTree(std::vector<Data> & allData, const Attribute & attrs, int level)
{
//    cout << "level = " << level << endl;
    Node * currNode = new Node();
    if( allData.size()==0 ) {
        currNode->isLeaf = true;
        currNode->hasValue = false;
        return currNode;
    }
    double purity = getPurity(allData);
    if( purity >= purityThreshold ){
        currNode->hasValue = true;
        currNode->isLeaf = true;
        currNode->canEat = true;
        currNode->updateCntEat(allData);
//        cout << " >= purityThreshold" << endl;
        return currNode;
    }
    if( purity <= (1-purityThreshold) ){
        currNode->hasValue = true;
        currNode->isLeaf = true;
        currNode->canEat = false;
        currNode->updateCntEat(allData);
//        cout << " <= purityThreshold" << endl;
        return currNode;
    }
    if( level>=attrs.getAttrSize()-2 ) {
        currNode->hasValue = true;
        currNode->isLeaf = true;
        if (purity>0.5) {
            currNode->canEat = true;
        }
        else {
            currNode->canEat = false;
        }
        currNode->updateCntEat(allData);
        return currNode;
    }
    
    vector< vector<Data> > splitedData;
    int bestSplit = GetMinSplit(allData, splitedData, attrs);
    currNode->question = bestSplit;
    
    // check one
    if( splitedData.size()!=attrs.getOneSize(bestSplit)+1 ) {
        cout << "Something Wrong!!! - ";
        cout << "DecisionTree::ConstructDecisionTree" << endl;
    }
    // check two
    int checksum = 0;
    for(int i=0; i<splitedData.size(); i+=1) {
        checksum += splitedData[i].size();
    }
    if( checksum!=allData.size() ) {
        cout << "Something Wrong!!! - ";
        cout << "DecisionTree::ConstructDecisionTree";
        cout << "Num of Data Incorrect!" << endl;
    }
    // ==========
    
    currNode->child.resize( attrs.getOneSize(bestSplit)+1 );
    for(int i=0; i<currNode->child.size(); i+=1) {
        currNode->child[i] = ConstructDecisionTree(splitedData[i], attrs, level+1);
    }
    
    currNode->updateCntEat();
    if( level==0 ) {
        head = currNode;
    }
    return currNode;
}

bool DecisionTree::PredictData(Data currData)
{
    Node * ptr = head;
    int ss = 0;
    while ( !ptr->hasValue ) {
        int childInd = currData.data[ ptr->question ];
        // 可以改成找不到就統計所有其他的 attribute算答案
        // 現在先找不到就改成下一個
        Node * tmpptr = ptr->child[ childInd ];
        while ( tmpptr->isNonValueLeaf() ) {
            tmpptr = ptr->child[ (++childInd) % ptr->child.size() ];
            ss += 1;
        }
        ptr = tmpptr;
    }
    if( ss )
        cout << ss << endl;
    return ptr->canEat;
}

void DecisionTree::PrintNode(Node * curr, int level)
{
    if( curr==nullptr ) {
        cout << "some nullptr case!" << endl;
        return ;
    }
    // if( curr->isLeaf ) return;
    if( curr->child.size()==0 ) return;
    
    printSpace(level);
    cout << "level= " << level << endl;
    printSpace(level);
    cout << "hasValue= " << curr->hasValue << endl;
    if (curr->hasValue) {
        printSpace(level);
        cout << "canEat= " << curr->canEat << endl;
    }
    
    printSpace(level);
    cout << "CntCanEat= " << curr->getCntCanEat() << ", ";
//    printSpace(level);
    cout << "CntCannotEat= " << curr->getCntCannotEat() << ", ";
//    printSpace(level);
    cout << "TotalEat= " << curr->getTotalCnt() << endl;
    printSpace(level);
    cout << "CanEatRate= " << curr->getCanEatRate() << ", ";
    cout << "CannotEatRate= " << curr->getCannotEateRate() << endl;
    
    printSpace(level);
    cout << "Num of child= " << curr->child.size() << endl;
    for(int i=0; i<curr->child.size(); i+=1) {
        printSpace(level);
        cout << "Index of child= " << i << endl;
        PrintNode(curr->child[i], level+1);
    }
    printSpace(level);
    for(int i=0; i<level; i+=1) cout << "    ";
    cout << "end of the Node" << endl << endl;
}

void DecisionTree::Print()
{
    PrintNode(head, 0);
}