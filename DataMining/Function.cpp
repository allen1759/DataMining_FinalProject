//
//  Function.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Function.h"
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

string & tolower(string & str)
{
    for(auto & ch : str) {
        ch = tolower(ch);
    }
    return str;
}

bool String2DataNoAnswer(std::string & origin, const Attribute & attrs, Data & onedata)
{
    string word;
    Data oned( attrs.getAttrSize() );
    stringstream ss(origin);
    // cout << ss.str() << endl;
    
    for(int i=0; i<oned.data.size(); i+=1) {
        ss >> word;
        word = tolower(word);
        if( word=="?" )
            oned.data[i] = 0;
        else {
            oned.data[i] = attrs.getMapping(i, word);
            if( oned.data[i]==0 ) {
                cout << "Error! Cannot find this attribute value." << endl;
                return false;
            }
        }
        // cout << oned.data[i] << " ";
    }
    // cout << endl;
    onedata = oned;
    
    return true;
}

bool String2Data(std::string & origin, const Attribute & attrs, Data & onedata)
{
    string word;
    Data oned( attrs.getAttrSize() );
    stringstream ss(origin);
    // cout << ss.str() << endl;
    ss >> word;
    if( word[0]=='E' )
        oned.setEat(true);
    else if( word[0]=='P' )
        oned.setEat(false);
    else {
        cout << "Error! I don't know what it is." << endl;
        return false;
    }
    
    for(int i=0; i<oned.data.size(); i+=1) {
        ss >> word;
        word = tolower(word);
        if( word=="?" )
            oned.data[i] = 0;
        else {
            oned.data[i] = attrs.getMapping(i, word);
            if( oned.data[i]==0 ) {
                cout << "Error! Cannot find this attribute value." << endl;
                return false;
            }
        }
        // cout << oned.data[i] << " ";
    }
    // cout << endl;
    onedata = oned;
    
    return true;
}

void InputAllDatas(std::fstream & in, std::vector<Data> & datas, const Attribute & attrs)
{
    string line, word;
    while ( getline(in, line) ) {
        if( line[0]=='/') continue;
        Data currd;
        if( String2Data(line, attrs, currd)) {
            datas.push_back( currd );
        }
        else {
            cout << "Cannot convert the string." << endl;
        }
    }
    
    random_shuffle(datas.begin(), datas.end(), RNG());
}

void PreProcess(const std::string & direct1, Attribute & attrs, const std::string & direct2, std::vector<Data> & allData, int trainingSize, std::vector<Data> & trainingData, std::vector<Data> & testingData)
{
    fstream in;
    in.open(direct1, ios::in);
    attrs.initial(in);
    in.close();
    
    in.open(direct2, ios::in);
    InputAllDatas(in, allData, attrs);
    trainingData.assign(allData.begin(), allData.begin()+trainingSize);
    testingData.assign(allData.begin()+trainingSize, allData.end());
    in.close();
}

void TrainingStep(DecisionTree & myTree, std::vector<Data> & trainingData, Attribute & attrs, SplitMethod meth)
{
    clock_t start_time, end_time;
    start_time = clock(); /* mircosecond */
    
    myTree.ConstructDecisionTree(trainingData, attrs, meth);
    
    end_time = clock();
    cout << "           ================ Training Step ================" << endl;
    cout << "               Training dataset size = " << trainingData.size() << endl;
    cout << "               Construct DecisionTree Time: " << static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC << "(seconds)"  << endl << endl;
}