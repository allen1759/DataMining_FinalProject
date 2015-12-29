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

void InputAllDatas(std::fstream & in, std::vector<Data> & datas, const Attribute & attrs)
{
    string line, word;
    while ( getline(in, line) ) {
        if( line[0]=='/') continue;
        Data oned( attrs.getAttrSize() );
        stringstream ss(line);
        cout << ss.str() << endl;
        ss >> word;
        if( word[0]=='E' )
            oned.setEat(true);
        else if( word[0]=='P' )
            oned.setEat(false);
        else
            cout << "Error! I don't know what it is." << endl;
        
        for(int i=0; i<oned.data.size(); i+=1) {
            ss >> word;
            word = tolower(word);
            cout << word[0] << " ";
            if( word=="?" )
                oned.data[i] = 0;
            else
                oned.data[i] = attrs.getMapping(i, word);
            cout << oned.data[i] << " ";
        }
        cout << endl;
        datas.push_back(oned);
    }
}