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
    int ConfusionMatrix[2][2];
    
public:
    int getTP() const;
    int getFN() const;
    int getFP() const;
    int getTN() const;
    void setTP(int value);
    void setFN(int value);
    void setFP(int value);
    void setTN(int value);
    
    void PrintMatrix() const;
};


#endif /* Evaluation_h */
