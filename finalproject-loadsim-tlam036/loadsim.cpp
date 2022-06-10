#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

#include "loadValueSim.h"

using namespace std;

int main(int argc, char *argv[]){
    ifstream traceFile;
    string s;
    string temp;
    float pred_correct;
    float total;
    uint64_t index;
    uint64_t addr;
    uint64_t value;

    //parse command line
    string fileName;
    float threshold;
    vector<string> parser;
    int output = 0;
    for(int i = 1; i < argc; i++){
        parser.push_back(argv[i]);
    }

    for(int i = 0; i < parser.size(); i++){
        if (parser[i] == "-f"){
            fileName = parser[i + 1];
        }
        if (parser[i] == "-t"){
            threshold = stof(parser[i + 1]);
        }

        if (parser[i] == "-o"){
            output = 1;
        }
    }
    
    //Calculate percentage confidence

    loadValueSim predictor;

    traceFile.open(fileName);
    if(traceFile.is_open()){
        while(getline(traceFile, s)){
            traceFile >> temp;
            istringstream converter(temp);
            converter >> std::hex >> index;
            traceFile >> temp;
            istringstream converter2(temp);
            converter2 >> std::hex >> addr;
            traceFile >> temp;
            istringstream converter3(temp);
            converter3 >> std::hex >> value;

            //Last value predictor
            predictor.confidenceCalculator(index, addr, value);
            
        }
    }
    else{
        cout << "Unable to open trace file" << endl;
        return -1;
    }
    traceFile.close();

    //Construct Confidence Binary

    traceFile.open(fileName);
    if(traceFile.is_open()){
        while(getline(traceFile, s)){
            traceFile >> temp;
            istringstream converter(temp);
            converter >> std::hex >> index;
            traceFile >> temp;
            istringstream converter2(temp);
            converter2 >> std::hex >> addr;
            traceFile >> temp;
            istringstream converter3(temp);
            converter3 >> std::hex >> value;

            //Last value predictor
            predictor.confidenceDecision(index, addr, threshold);
            
        }
    }
    else{
        cout << "Unable to open trace file" << endl;
        return -1;
    }
    traceFile.close();
    predictor.clearPredictor();

    //Last Value Predictor

    cout << "LAST VALUE PREDICTOR" << endl;
    cout << "--------------------------------------------------" << endl;
    traceFile.open(fileName);
    if(traceFile.is_open()){
        while(getline(traceFile, s)){
            traceFile >> temp;
            istringstream converter(temp);
            converter >> std::hex >> index;
            traceFile >> temp;
            istringstream converter2(temp);
            converter2 >> std::hex >> addr;
            traceFile >> temp;
            istringstream converter3(temp);
            converter3 >> std::hex >> value;

            //Last value predictor
            pair<uint64_t, float> outputResult = predictor.lastValuePredictor(index, addr, value);
            if(output){
                cout << outputResult.first << " " << outputResult.second << endl;
            }
            
        }
    }
    else{
        cout << "Unable to open trace file" << endl;
        return -1;
    }
    traceFile.close();

    predictor.printStat();
    cout << "--------------------------------------------------" << endl;
   
    return 0;
}