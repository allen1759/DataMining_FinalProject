//
//  Data.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Data.h"

Data::Data(int size)
{
    data.resize(size);
}

void Data::setEat(bool ans)
{
    canEat = ans;
}
