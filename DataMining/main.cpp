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
using namespace std;

int main(int argc, const char * argv[])
{
    
    fstream in;
    in.open("/Users/Allen/Documents/workspace/DataMining/expanded.txt", ios::in);
    string line;
    while( getline(in, line) ) {
        cout << line << endl;
    }
    
    cout << "Hello, World!\n";
    
    return 0;
}
