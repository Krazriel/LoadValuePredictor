#ifndef LOAD_VALUE_SIM
#define LOAD_VALUE_SIM

#include <map>
#include <iomanip>
#include <iostream>

using namespace std;

class loadValueSim{
    public:
        loadValueSim();
        pair<uint64_t, float> lastValuePredictor(uint64_t index, uint64_t addr, uint64_t value);
        void confidenceCalculator(uint64_t index, uint64_t addr, uint64_t value);
        void confidenceDecision(uint64_t index, uint64_t addr, float threshold);
        void clearPredictor();
        void printStat();
    private:
        uint64_t historyIndex;
        float threshold;
        float pred_correct;
        float total;
        float totalData;
        map< pair<uint64_t, uint64_t> , uint64_t> predictor;
        map< pair<uint64_t, uint64_t> , pair<float, float> > confidenceTable;
        map< pair<uint64_t, uint64_t> , float> confidenceBinary;
};

#endif