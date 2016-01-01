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

double Evaluation::getAccuracy() const
{
    return accuracy;
}
double Evaluation::getPrecision() const
{
    return precision;
}
double Evaluation::getRecall() const
{
    return recall;
}
double Evaluation::getF_measure() const
{
    return F_measure;
}

void Evaluation::update()
{
    ConfusionMatrix[0][2] = getTP() + getFN();
    ConfusionMatrix[1][2] = getFP() + getTN();
    ConfusionMatrix[2][0] = getTP() + getFP();
    ConfusionMatrix[2][1] = getFN() + getTN();
    ConfusionMatrix[2][2] = ConfusionMatrix[2][0] + ConfusionMatrix[2][1];
    
    accuracy = static_cast<double>(getTP()+getTN()) / ConfusionMatrix[2][2];
    precision = static_cast<double>(getTP()) / ConfusionMatrix[0][2];
    recall = static_cast<double>(getTP()) / ConfusionMatrix[2][0];
    F_measure = 2*precision*recall / (precision+recall);
}

//                   Predicted class
//           -------------------------------
//           |   \\  |    yes   |    no    |
//           |-----------------------------|
//    Actual |  yes  |          |          |
//    class  |-----------------------------|
//           |  no   |          |          |
//           -------------------------------
void Evaluation::PrintMatrix() const
{
    
    printf("                             Predicted class\n");
    printf("           -------------------------------------------------\n");
    printf("           |     \\     |   Edible  | Poisonous |    Sum    |\n");
    printf("           |-----------------------------------------------|\n");
    printf("    Actual |   Edible  |%8d   |%8d   |%8d   |\n", getTP(), getFN(), ConfusionMatrix[0][2]);
    printf("           |-----------------------------------------------|\n");
    printf("    class  | Poisonous |%8d   |%8d   |%8d   |\n", getFP(), getTN(), ConfusionMatrix[1][2]);
    printf("           |-----------------------------------------------|\n");
    printf("           |    Sum    |%8d   |%8d   |%8d   |\n", ConfusionMatrix[2][0], ConfusionMatrix[2][1], ConfusionMatrix[2][2]);
    printf("           -------------------------------------------------\n\n");
    
    printf("               Accuracy  = %.4f%% ((a+d)/(a+b+c+d))\n", 100*accuracy);
    printf("               Precision = %.4f%% (a/(a+c))\n", 100*precision);
    printf("               Recall    = %.4f%% (a/(a+b)\n", 100*recall);
    printf("               F-measure = %.4f%% (2rp/(r+p))\n", 100*F_measure);
}
