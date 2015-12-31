//
//  Function.h
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#ifndef Function_h
#define Function_h

// #include <vector>
// #include <fstream>
#include "Data.h"
#include "Attribute.h"
#include "Node.h"

struct RNG {
    int operator() (int n) {
        return std::rand() / (1.0 + RAND_MAX) * n;
    }
};

std::string & tolower(std::string & str);
bool String2Data(std::string & origin, const Attribute & attrs);
bool String2DataNoAnswer(std::string & origin, const Attribute & attrs, Data & onedata);
void InputAllDatas(std::fstream & in, std::vector<Data> & datas, const Attribute & attrs);


#endif /* Function_h */
