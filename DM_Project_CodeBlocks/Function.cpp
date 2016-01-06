//
//  Function.cpp
//  DataMining
//
//  Created by 楊智偉 on 12/29/15.
//  Copyright © 2015 楊智偉. All rights reserved.
//

#include "Function.h"
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

string & tolower(string & str)
{
    for(auto & ch : str) {
        ch = tolower(ch);
    }
    return str;
}

bool String2DataNoAnswer(std::string & origin, const Attribute & attrs, Data & onedata)
{
    string word;
    Data oned( attrs.getAttrSize() );
    stringstream ss(origin);
    // cout << ss.str() << endl;

    for(int i=0; i<oned.data.size(); i+=1) {
        ss >> word;
        word = tolower(word);
        if( word=="?" )
            oned.data[i] = 0;
        else {
            oned.data[i] = attrs.getMapping(i, word);
            if( oned.data[i]==0 ) {
                cout << "Error! Cannot find this attribute value." << endl;
                return false;
            }
        }
        // cout << oned.data[i] << " ";
    }
    // cout << endl;
    onedata = oned;

    return true;
}

bool String2Data(std::string & origin, const Attribute & attrs, Data & onedata)
{
    string word;
    Data oned( attrs.getAttrSize() );
    stringstream ss(origin);
    // cout << ss.str() << endl;
    ss >> word;
    if( word[0]=='E' )
        oned.setEat(true);
    else if( word[0]=='P' )
        oned.setEat(false);
    else {
        cout << "Error! I don't know what it is." << endl;
        return false;
    }

    for(int i=0; i<oned.data.size(); i+=1) {
        ss >> word;
        word = tolower(word);
        if( word=="?" )
            oned.data[i] = 0;
        else {
            oned.data[i] = attrs.getMapping(i, word);
            if( oned.data[i]==0 ) {
                cout << "Error! Cannot find this attribute value." << endl;
                return false;
            }
        }
        // cout << oned.data[i] << " ";
    }
    // cout << endl;
    onedata = oned;

    return true;
}

void InputAllDatas(std::fstream & in, std::vector<Data> & datas, const Attribute & attrs)
{
    string line, word;
    while ( getline(in, line) ) {
        if( line[0]=='/') continue;
        Data currd;
        if( String2Data(line, attrs, currd)) {
            datas.push_back( currd );
        }
        else {
            cout << "Cannot convert the string." << endl;
        }
    }

    random_shuffle(datas.begin(), datas.end(), RNG());
}

void PreProcess(const std::string & direct1, Attribute & attrs, const std::string & direct2, std::vector<Data> & allData, int trainingSize, std::vector<Data> & trainingData, std::vector<Data> & testingData)
{
    fstream in;
    in.open(direct1, ios::in);
    attrs.initial(in);
    in.close();

    in.open(direct2, ios::in);
    InputAllDatas(in, allData, attrs);
    trainingData.assign(allData.begin(), allData.begin()+trainingSize);
    testingData.assign(allData.begin()+trainingSize, allData.end());
    in.close();
}

void TrainingStep(DecisionTree & myTree, std::vector<Data> & trainingData, Attribute & attrs, SplitMethod meth, Evaluation & eval, bool print)
{
    clock_t start_time, end_time;
    start_time = clock(); /* mircosecond */

    myTree.ConstructDecisionTree(trainingData, attrs, meth);

    end_time = clock();
    eval.addTrainingTime(static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC);

    if( print ) {
        cout << "           ================ Training Step ================" << endl;
        cout << "               Training dataset size = " << trainingData.size() << endl;
        cout << "               Construct DecisionTree Time: " << static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC << "(seconds)"  << endl << endl;
    }
}

void TestingStep(DecisionTree & myTree, std::vector<Data> & testingData, Evaluation & eval, bool print)
{
    clock_t start_time, end_time;
    start_time = clock(); /* mircosecond */

    for(auto & data : testingData) {
        bool predicted = myTree.PredictData(data);
        if( data.canEat && predicted ) {
            eval.setTP( eval.getTP()+1 );
        }
        else if( data.canEat && !predicted ) {
            eval.setFN( eval.getFN()+1 );
        }
        else if( !data.canEat && predicted ) {
            eval.setFP( eval.getFP()+1 );
        }
        else if( !data.canEat && !predicted ) {
            eval.setTN( eval.getTN()+1 );
        }
    }

    end_time = clock();

    eval.addTestingTime(static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC);
    eval.update();
    if( print ) {
        cout << "           ================ Predicting Step ================" << endl;
        cout << "               Testing dataset size = " << testingData.size() << endl << endl;
        eval.PrintMatrix();
        cout << "               Precict using Time: " << static_cast<double>(end_time - start_time)/CLOCKS_PER_SEC << "(seconds)" << endl << endl;
    }
}

void Print2FileAttrs(std::fstream & out)
{
    out << "Total_size\t";
    out << "Train_size\t";
    out << "Test_size\t" ;
    out << "TP\tFN\tFP\tTN\t";
    out << "Accuracy\tPrecision\tRecall\tF_measure\t";
    out << "Training_time\t";
    out << "Testing_time" << endl;
}

void Print2File(std::fstream & out, std::vector<Data> & trainingData, std::vector<Data> & testingData, Evaluation & eval)
{
    out << trainingData.size()+testingData.size() << "\t";
    out << trainingData.size() << "\t";
    out << testingData.size() << "\t";
    out << eval.getTP() << "\t" << eval.getFN() << "\t" << eval.getFP() << "\t" << eval.getTN() << "\t";
    out << eval.getAccuracy() << "\t" << eval.getPrecision() << "\t" << eval.getRecall() << "\t" << eval.getF_measure() << "\t";
    out << eval.getTrainingTime() << "\t" << eval.getTestingTime() << endl;
}

void PredictLoop(DecisionTree & mytree, const Attribute & attr)
{
    cout << endl << endl;
    cout << "Start to Predict Mushroom!!!" << endl;
    string word;
    string allinfo[25] = { "1. cap-shape: bell=b conical=c convex=x flat=f knobbed=k sunken=s",
                           "2. cap-surface: fibrous=f grooves=g scaly=y smooth=s",
                           "3. cap-color: brown=n buff=b cinnamon=c gray=g green=r pink=p purple=u red=e white=w yellow=y",
                           "4. bruises?: bruises=t no=f",
                           "5. odor: almond=a anise=l creosote=c fishy=y foul=f musty=m none=n pungent=p spicy=s",
                           "6. gill-attachment: attached=a descending=d free=f notched=n",
                           "7. gill-spacing: close=c crowded=w distant=d",
                           "8. gill-size: broad=b narrow=n",
                           "9. gill-color: black=k brown=n buff=b chocolate=h gray=g green=r orange=o pink=p purple=u red=e white=w yellow=y",
                           "10. stalk-shape: enlarging=e tapering=t",
                           "11. stalk-root: bulbous=b club=c cup=u equal=e rhizomorphs=z rooted=r missing=?",
                           "12. stalk-surface-above-ring: fibrous=f scaly=y silky=k smooth=s",
                           "13. stalk-surface-below-ring: fibrous=f scaly=y silky=k smooth=s",
                           "14. stalk-color-above-ring: brown=n buff=b cinnamon=c gray=g orange=o pink=p red=e white=w yellow=y",
                           "15. stalk-color-below-ring: brown=n buff=b cinnamon=c gray=g orange=o pink=p red=e white=w yellow=y",
                           "16. veil-type: partial=p universal=u",
                           "17. veil-color: brown=n orange=o white=w yellow=y",
                           "18. ring-number: none=n one=o two=t",
                           "19. ring-type: cobwebby=c evanescent=e flaring=f large=l none=n pendant=p sheathing=s zone=z",
                           "20. spore-print-color: black=k brown=n buff=b chocolate=h green=r orange=o purple=u white=w yellow=y",
                           "21. population: abundant=a clustered=c numerous=n scattered=s several=v solitary=y",
                           "22. habitat: grasses=g leaves=l meadows=m paths=p urban=u waste=w woods=d" };
    do {
        Data newData(attr.getAttrSize());
        for(int i=0; i<attr.getAttrSize(); i+=1) {
            cout << allinfo[i] << endl;
            cin >> word;
            newData.data[i] = attr.getMapping(i, word);
        }
        if( mytree.PredictData(newData) ) {
            cout << "Predict: Edible" << endl;
        }
        else {
            cout << "Predict: Poisonous" << endl;
        }

        cout << "have another Mushroom need to predict(y/n)...>";
        cin >> word;
        tolower(word);
    } while( word[0]=='y' );
}
