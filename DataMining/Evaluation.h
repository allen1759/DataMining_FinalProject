//
//  Evaluation.h
//  DataMining
//
//  Created by 楊智偉 on 12/31/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#ifndef Evaluation_h
#define Evaluation_h

//                Predicted
//           ----------------
//           | \\ | yes| no |
//           |--------------|
//    actual |yes | TP | FN |
//           |--------------|
//    class  | no | FP | TN |
//           ----------------

class Evaluation
{
private:
    int ConfusionMatrix[3][3];
    double accuracy;
    double precision;
    double recall;
    double F_measure;
    double trainingTime = 0;
    double testingTime = 0;
    
public:
    Evaluation()
    {
        for(int i=0; i<3; i+=1) {
            for(int j=0; j<3; j+=1) {
                ConfusionMatrix[i][j] = 0;
            }
        }
    }
    int getTP() const;
    int getFN() const;
    int getFP() const;
    int getTN() const;
    void setTP(int value);
    void setFN(int value);
    void setFP(int value);
    void setTN(int value);
    double getAccuracy() const;
    double getPrecision() const;
    double getRecall() const;
    double getF_measure() const;
    void addTrainingTime(double num)
    {
        trainingTime += num;
    }
    void addTestingTime(double num)
    {
        testingTime += num;
    }
    double getTrainingTime() const
    {
        return trainingTime;
    }
    double getTestingTime() const
    {
        return testingTime;
    }
    
    void update();
    void PrintMatrix() const;
};


#endif /* Evaluation_h */
