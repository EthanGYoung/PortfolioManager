//
// Created by Ethan Young on 1/1/18.
//
//Test to see if it worked
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
    std::vector<tm *> *dates;
    std::map<string, Stock> *sl;
    std::map<std::string, double> *percentCorrect;
    std::map<std::string, double> *increase;
    vector<string> *factorNames;
    int numDays;
    int startDate;
    int interval;
    tm *predictDate;
    Algorithm *al;
    Fund *fund;
    int dayUnknown;
    double btResults(double* results);
    Backtest(Fund *fundEx, int interva, vector<string> *factors, int numDay, tm *predictedDate, bool unknown);
    virtual ~Backtest();
    void runBacktestStocks();
    double userBacktestMain();
    void calcPrevDayChange();
    void calcPercentCorrect();
    void predictDay();
    int getDateIndx(tm *Date);

};


#endif //BACKTEST_H
