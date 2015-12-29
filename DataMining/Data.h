//
//  Data.h
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#ifndef Data_h
#define Data_h

#include <vector>

class Data
{
private:
    std::vector<int> data;
    
public:
    Data() = default;
    Data(int size)
    {
        data.resize(size);
    }
};

#endif /* Data_h */
