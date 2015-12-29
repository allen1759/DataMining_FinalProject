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
#include <string>

class Data
{
public:
    bool canEat;
    std::vector<int> data;
    
    Data() = default;
    Data(int size)
    {
        data.resize(size);
    }
    
    void setEat(bool ans)
    {
        canEat = ans;
    }
};

#endif /* Data_h */
