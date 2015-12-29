//
//  main.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Function.h"
#include "Attribute.h"
#include "Data.h"
using namespace std;

int main(int argc, const char * argv[])
{
    fstream in;
    in.open("/Users/Allen/Documents/workspace/DataMining/attributes.txt", ios::in);
    Attribute attrs;
    attrs.initial(in);
    in.close();
    
    in.open("/Users/Allen/Documents/workspace/DataMining/expanded.txt", ios::in);
    vector<Data> allData;
    InputAllDatas(in, allData, attrs);
    
    cout << "Hello, World!\n";
    
    return 0;
}
