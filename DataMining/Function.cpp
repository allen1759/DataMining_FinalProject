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

#include <iostream>
using namespace std;

string & tolower(string & str)
{
    for(auto & ch : str) {
        ch = tolower(ch);
    }
    return str;
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
}
