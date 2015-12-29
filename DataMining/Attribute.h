//
//  Attribute.h
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#ifndef Attribute_h
#define Attribute_h

#include "Attribute.h"
#include <fstream>
#include <vector>
#include <map>
#include <string>

class Attribute
{
private:
    int attrSize;
    std::vector< std::map<std::string, int> > record;
    
public:
    void initial(std::fstream & in);
    int getAttrSize() const;
    int getMapping(int attnum, std::string name) const;
};

#endif /* Attribute_h */
