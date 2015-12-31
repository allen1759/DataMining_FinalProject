//
//  Node.h
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <vector>
#include "Data.h"

class Node
{
private:
    int cntCanEat = 0;
    int cntCannotEat = 0;
    
public:
    bool isLeaf = false;
    bool hasValue = false;
    bool canEat;
    int question;
    // 每一個分枝的值
    // std::vector<int> value;
    // 每一個分枝的 child node
    std::vector<Node *> child;
    int getCntCanEat() const
    {
        return cntCanEat;
    }
    int getCntCannotEat() const
    {
        return cntCannotEat;
    }
    int getTotalCnt() const
    {
        return cntCanEat + cntCannotEat;
    }
    double getCanEatRate() const
    {
        return static_cast<double>(cntCanEat) / getTotalCnt();
    }
    double getCannotEateRate() const
    {
        return static_cast<double>(cntCannotEat) / getTotalCnt();
    }
    // case for non-hasValue node.
    void updateCntEat()
    {
        cntCanEat = 0;
        cntCannotEat = 0;
        
        for( auto & ptr : child ) {
            cntCanEat += ptr->getCntCanEat();
            cntCannotEat += ptr->getCntCannotEat();
        }
    }
    // case for hasValue node.
    void updateCntEat(std::vector<Data> & arr)
    {
        cntCanEat = 0;
        cntCannotEat = 0;
        for( auto &e : arr ) {
            if( e.canEat )
                cntCanEat += 1;
            else
                cntCannotEat += 1;
        }
    }
};

#endif /* Node_h */
