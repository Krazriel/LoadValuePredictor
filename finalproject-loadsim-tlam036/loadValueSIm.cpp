#include "loadValueSim.h"

loadValueSim::loadValueSim(){
    historyIndex = 0;
    pred_correct = 0.0;
    total = 0.0;
}

void loadValueSim::clearPredictor(){
    predictor.clear();
}

//calculates confidence binary to table
void loadValueSim::confidenceDecision(uint64_t index, uint64_t addr, float threshold){
    this->threshold = threshold;
    pair<uint64_t, uint64_t> key = make_pair(index, addr);
    if(confidenceBinary.find(key) == confidenceBinary.end()){
        if(confidenceTable[key].first / confidenceTable[key].second >= threshold){
            confidenceBinary[key] = 1;
        }
        else{
            confidenceBinary[key] = 0;
        }
    }
}

//calculate confidence ratio to table
void loadValueSim::confidenceCalculator(uint64_t index, uint64_t addr, uint64_t value){
    pair<uint64_t, uint64_t> key = make_pair(index, addr);
    if(confidenceTable.find(key) == confidenceTable.end()){
        if(value == 0){
            pair<float, float> confRatio = make_pair(1.0, 1.0);
            confidenceTable[key] = confRatio;
            predictor[key] = value;
        }
        else{
            pair<float, float> confRatio = make_pair(0.0, 1.0);
            confidenceTable[key] = confRatio;
            predictor[key] = value;
        }
    }
    else{
        if(predictor[key] == value){
            confidenceTable[key].first += 1;
            confidenceTable[key].second += 1;
        }
        else{
            predictor[key] = value;
            confidenceTable[key].second += 1;
        }
    }
}

pair<uint64_t, float> loadValueSim::lastValuePredictor(uint64_t index, uint64_t addr, uint64_t value){
    pair<uint64_t, uint64_t> key = make_pair(index, addr);
    uint64_t predicted;
    if(confidenceBinary[key] == 1){
        if(predictor.find(key) == predictor.end()){
            predicted = 0;
            if(value == 0){
                predictor[key] = value;
                pred_correct++;
            }
            else{
                predictor[key] = value;
            }
        }
        else{
            predicted = predictor[key];
            if(predictor[key] == value){
                pred_correct++;
            }
            else{
                predictor[key] = value;
            }
        }
        total++;
        totalData++;
    }
    else{
        totalData++;
    }

    pair<uint64_t, float> result = make_pair(predicted, confidenceBinary[key]);
    return result;
}

void loadValueSim::printStat(){
    cout << setprecision(2) << fixed;
    cout << "[THRESHOLD] : " << 100 * threshold << "%" << endl;
    cout << "[PERCENTAGE OF TRACE PREDICTED] : " << 100 * (total / totalData) << "%" << endl;
    cout << "[CORRECT] : " << pred_correct << endl;
    cout << "[TOTAL] : " << total << endl;
    cout << "[ACCURACY] : " << 100 * (pred_correct / total) << "%" << endl;
}