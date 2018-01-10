//
// Created by Ethan Young on 1/1/18.
//

#ifndef BACKTEST_H
#define BACKTEST_H
#include "Algorithm.h"
#include <vector>
#include <ctime>
#include "Fund.h"
#include <map>
#include <string>
#include "Stock.h"
#include "Config.h"

extern std::string backtestPrompt;

class Backtest {
public:
    //String is stock name, map is date to actual
    std::map<std::string, std::map<int,double>*> actuals;
    std::map<std::string, std::map<int,double>*> predicted;
    std::map<std::string, std::map<int,double>*> difference;
    std::map<std::string, std::map<int,double>*> prevDayDiffPred;
    std::map<std::string, std::map<int,double>*> prevDayDiffActual;
    std::map<std::string, double> percentCorrect;
    Backtest(Fund *fund);
    virtual ~Backtest();
    void runBacktestStocks(Algorithm *al, Fund *fund, vector<string> *fa, int numDays, int startDate);
    bool compareDirection(double prediction, double actual);
    double compareMagnitude(double prediction, double actual);
    void userBacktestMain(Fund *fund);
    void analyzeResults(Fund *fund);
    void calcPrevDayChange(Fund *fund, int numDays, int startDate);
    void calcPercentCorrect(Fund *fund, int numDays, int startDate);
};


#endif //BACKTEST_H
