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

class Node
{
public:
    bool isLeaf = false;
    bool hasValue = false;
    bool canEat;
    int question;
    int cntCanEat = 0;
    int cntCannotEat = 0;
    // 每一個分枝的值
    // std::vector<int> value;
    // 每一個分枝的 child node
    std::vector<Node *> child;
};

#endif /* Node_h */
