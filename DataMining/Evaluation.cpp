//
//  Evaluation.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/31/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Evaluation.h"

int Evaluation::getTP() const
{
    return ConfusionMatrix[0][0];
}
int Evaluation::getFN() const
{
    return ConfusionMatrix[0][1];
}
int Evaluation::getFP() const
{
    return ConfusionMatrix[1][0];
}
int Evaluation::getTN() const
{
    return ConfusionMatrix[1][1];
}

void Evaluation::setTP(int value)
{
    ConfusionMatrix[0][0] = value;
}
void Evaluation::setFN(int value)
{
    ConfusionMatrix[0][1] = value;
}
void Evaluation::setFP(int value)
{
    ConfusionMatrix[1][0] = value;
}
void Evaluation::setTN(int value)
{
    ConfusionMatrix[1][1] = value;
}
