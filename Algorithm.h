//
// Created by Ethan Young on 1/1/18.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <ctime>
#include "Fund.h"


class Algorithm {
public:
    Algorithm(int interval, Fund *fund, vector<string> *factorNames, int budget, int numPur, double upperLim, double lowerLim);
    virtual ~Algorithm();
    double predictDate(tm *Date, Stock *st);
    double* selectStockDistribution(map<string, double> *percentCorrect, map<string, double> *increase);
private:
    int getDateIndex(tm* Date, Stock *st, Fund *fund);
    double getPrediction(double result[], vector<string> *faName, Stock *stk, int date, vector<tm*> *dates);
    int testInterval;
    Fund *fund;
    vector<string> *faName;
    std::map<string, Stock> *stockList;
    //Initialize in algorithm when ready
    int totalBudget;
    int numDiffPurchased;
    double upperPercentLimit;
    double lowerPercentLimit;
};


#endif //ALGORITHM_H
