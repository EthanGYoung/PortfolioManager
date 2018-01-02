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
    Backtest();
    virtual ~Backtest();
    void runBacktestStocks(Algorithm *algo, std::vector<tm> Dates, Fund *fund);
    bool compareDirection(double prediction, double actual);
    double compareMagnitude(double prediction, double actual);
    void userBacktestMain(Fund *fund);
};


#endif //BACKTEST_H
