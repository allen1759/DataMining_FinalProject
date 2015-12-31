//
//  Evaluation.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/31/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Evaluation.h"
#include <cstdio>
using namespace std;

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

//                   Predicted class
//           -------------------------------
//           |   \\  |    yes   |    no    |
//           |-----------------------------|
//    Actual |  yes  |    10    |    10    |
//    class  |-----------------------------|
//           |  no   |          |          |
//           -------------------------------
void Evaluation::PrintMatrix() const
{
    printf("                     Predicted class\n");
    printf("           -------------------------------------\n");
    printf("           |     \\     |   edible  | poisonous |\n");
    printf("           |-----------------------------------|\n");
    printf("    Actual |   edible  |%11d|%11d|\n", ConfusionMatrix[0][0], ConfusionMatrix[0][1]);
    printf("    class  |-----------------------------------|\n");
    printf("           | poisonous |%11d|%11d|\n", ConfusionMatrix[1][0], ConfusionMatrix[1][1]);
    printf("           -------------------------------------\n");
}
