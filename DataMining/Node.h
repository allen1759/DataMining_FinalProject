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
    int level = 0;
    int question = 0;
    // 每一個分枝的值
    // std::vector<int> value;
    // 每一個分枝的 child node
    std::vector<Node *> child;
    void setLevel(int le);
    bool isNonValueLeaf() const;
    int getCntCanEat() const;
    int getCntCannotEat() const;
    int getTotalCnt() const;
    double getCanEatRate() const;
    double getCannotEateRate() const;
    // case for non-hasValue node.
    void updateCntEat();
    // case for hasValue node.
    void updateCntEat(std::vector<Data> & arr);
};

#endif /* Node_h */
