//
//  Attribute.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Attribute.h"
#include <sstream>
using namespace std;

void Attribute::initial(fstream & in)
{
    attrSize = 0;
    
    string input, word;
    while( getline(in, input) ) {
        record.push_back( map<string,int>() );
        
        // handle every line
        stringstream ss(input);
        int cnt = 0;
        while( ss>>word ) {
            if( word[ word.size()-1 ] == ':' )
                break;
        }
        while( ss>>word ) {
            string abbr = word.substr(word.length()-1);
            word = word.substr(0, word.length()-2);
            // cout << "word = " << word << ": " << cnt+1 << endl;
            record[attrSize][word] = ++cnt;
            record[attrSize][abbr] = cnt;
        }
        attrSize += 1;
    }
}

int Attribute::getOneSize(int i) const
{
    // if( i>=record.size() )
        // cout << "recod size error!" << endl;
    return static_cast<int>( record[i].size() );
}

int Attribute::getAttrSize() const
{
    return attrSize;
}

int Attribute::getMapping(int attnum, std::string name) const
{
    return record[attnum].find(name)->second;
}