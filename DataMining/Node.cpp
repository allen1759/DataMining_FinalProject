//
//  Node.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/31/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Node.h"
using namespace std;

void Node::setLevel(int le)
{
    level = le;
}
bool Node::isNonValueLeaf() const
{
    return isLeaf && !hasValue;
}
int Node::getCntCanEat() const
{
    return cntCanEat;
}
int Node::getCntCannotEat() const
{
    return cntCannotEat;
}
int Node::getTotalCnt() const
{
    return cntCanEat + cntCannotEat;
}
double Node::getCanEatRate() const
{
    return static_cast<double>(cntCanEat) / getTotalCnt();
}
double Node::getCannotEateRate() const
{
    return static_cast<double>(cntCannotEat) / getTotalCnt();
}
// case for non-hasValue node.
void Node::updateCntEat()
{
    cntCanEat = 0;
    cntCannotEat = 0;
    
    for( auto & ptr : child ) {
        if( ptr->isNonValueLeaf() ) {
            continue;
        }
        cntCanEat += ptr->getCntCanEat();
        cntCannotEat += ptr->getCntCannotEat();
    }
}
// case for hasValue node.
void Node::updateCntEat(std::vector<Data> & arr)
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