//
// Created by Ethan Young on 1/1/18.
//

#include "Backtest.h"
#include <iostream>

using namespace std;


Backtest::Backtest(Fund *fund) {
    map<string, Stock> *sl = fund->getStockList();
    map<string, Stock>::iterator it;

    //Initialize actuals and predicted
    for (it = sl->begin(); it != sl->end(); it++) {
        actuals.insert(pair<string, std::map<int, double> *>(it->second.getName(), new std::map<int, double>()));
        predicted.insert(pair<string, std::map<int, double> *>(it->second.getName(), new std::map<int, double>()));
        difference.insert(pair<string, std::map<int, double> *>(it->second.getName(), new std::map<int, double>()));
        prevDayDiffPred.insert(
                pair<string, std::map<int, double> *>(it->second.getName(), new std::map<int, double>()));
        prevDayDiffActual.insert(
                pair<string, std::map<int, double> *>(it->second.getName(), new std::map<int, double>()));
    }
}

Backtest::~Backtest() {
    // TODO Auto-generated destructor stub
}

//Calls algorithm methods to predict dates in Dates using stocks in fund (Predicts all stocks)
//Writes results to the fund (Maybe do 30 day results and 10 day results
void Backtest::runBacktestStocks(Algorithm *al, Fund *fund, vector<string> *fa, int numDays, int startDate) {
    cout << "Running Backtest in backtest" << endl;
    map<string, Stock> *sl = fund->getStockList();
    map<string, Stock>::iterator it;
    vector<tm *> *dates = fund->getDateList();
    vector<tm *>::iterator itr;


    //Loop through all stocks
    for (it = sl->begin(); it != sl->end(); it++) {
        itr = dates->begin() + startDate;
        //Loop through each date within the stock
        for (int i = 0; i < numDays; i++) {

            double pred = al->predictDate(fund, *itr, fund->getStock(it->second.getName()), fa);
            double actual = fund->getStock(it->second.getName())->getFactorValue("OpenPrice", *itr);
            map<int,double>* actList = actuals.find(it->second.getName())->second;
            (*actList)[it->second.convertDate(*itr)] = actual;
    cout << "Test actual";
            (*(predicted.find(it->second.getName())->second))[it->second.convertDate(*itr)] = pred;
            (*(difference.find(it->second.getName())->second))[it->second.convertDate(*itr)] = actual - pred;

            //Predicts the current date with the stock iterating through
            //it->second.addPred("Regression", pred, it->second.convertDate(*itr));
            itr++;
        }
    }
    cout << "End of backTestStock" << endl;
}

//Returns true if in same direction
bool Backtest::compareDirection(double prediction, double actual) {
    return ((prediction / actual) > 0);
}

//Returns the difference in magnitude between actual and predicted
double Backtest::compareMagnitude(double prediction, double actual) {
    return actual - prediction;
}

void Backtest::userBacktestMain(Fund *fund) {
    cout << "Running Backtest main in backtest" << endl;
    cout << backtestPrompt;
    Algorithm *al = new Algorithm();

    string algo;
    string period;
    string date;

    cout << "Algorithm:" << endl;
    cin >> algo;

    cout << "Period (int):" << endl;
    cin >> period;

    cout << "Starting Date (Default 50 in ):" << endl;
    cin >> date;

    //Prompt user for possible factors to include
    vector<string> *fa = new vector<string>();
    fa->push_back("LowPrice");
    fa->push_back("HighPrice");
    fa->push_back("Volume");

    runBacktestStocks(al, fund, fa, 500, 50);
    calcPrevDayChange(fund, 500, 50);
    calcPercentCorrect(fund, 500, 50);

}

void Backtest::analyzeResults(Fund *fund) {
    //Gets the stock list
    map<string, Stock> *sl = fund->getStockList();
    map<string, Stock>::iterator it;
    vector<tm *> *dates = fund->getDateList();
    vector<tm *>::iterator itr;


    //Compare actual to predicted for each date (Need start date, length, and actual/predicted for each)

}

void Backtest::calcPrevDayChange(Fund *fund, int numDays, int startDate) {
    cout << "Calc Prev Day Change" << endl;
    map<string, Stock> *sl = fund->getStockList();
    map<string, Stock>::iterator it;
    vector<tm *> *dates = fund->getDateList();
    vector<tm *>::iterator itr;


    //Loop through all stocks
    for (it = sl->begin(); it != sl->end(); it++) {
        itr = dates->begin() + startDate;
        //Loop through each date within the stock
        for (int i = 0; i < numDays; i++) {
            double actualCurrDay = (*(actuals.find(it->second.getName())->second))[it->second.convertDate(*itr)];
            double actualPrevDay = (*(actuals.find(it->second.getName())->second))[it->second.convertDate(*(itr - 1))];
            double predCurrDay = (*(predicted.find(it->second.getName())->second))[it->second.convertDate(*itr)];
            double predPrevDay = (*(actuals.find(it->second.getName())->second))[it->second.convertDate(*(itr - 1))];

            //cout << "1prevPredictedDiff: " << predCurrDay - predPrevDay << endl;
            //cout << "2prevActualDiff: " << actualCurrDay - actualPrevDay << endl;

            (*(prevDayDiffActual.find(it->second.getName())->second))[it->second.convertDate(*itr)] =
                    actualCurrDay - actualPrevDay;
            (*(prevDayDiffPred.find(it->second.getName())->second))[it->second.convertDate(*itr)] = predCurrDay -predPrevDay;

            itr++;
        }
    }
    cout << "End of calcPrevDayChange" << endl;
}

void Backtest::calcPercentCorrect(Fund *fund, int numDays, int startDate) {
    cout << "CalcPercentCorrect" << endl;
    map<string, Stock> *sl = fund->getStockList();
    map<string, Stock>::iterator it;
    vector<tm *> *dates = fund->getDateList();
    vector<tm *>::iterator itr;

    int correct = 0;
    int total = 0;
    //Loop through all stocks
    for (it = sl->begin(); it != sl->end(); it++) {

        itr = dates->begin() + startDate;

        //Loop through each date within the stock
        for (int i = 0; i < numDays; i++) {

            //cout << "1Predicted Prev Day: " << prevDayDiffPred.find(it->second.getName())->second->find(it->second.convertDate(*itr))->second << endl;
            //cout << "2Predicted Prev Day: " << prevDayDiffActual.find(it->second.getName())->second->find(it->second.convertDate(*itr))->second << endl;

            if ((*(prevDayDiffPred.find(it->second.getName())->second))[it->second.convertDate(*itr)] > 0.0 &&
                    (*(prevDayDiffActual.find(it->second.getName())->second))[it->second.convertDate(*itr)] > 0.0) {

                //cout << "Correct" << endl;
                //cout << "Actual Diff: " << (*(prevDayDiffActual.find(it->second.getName())->second))[it->second.convertDate(*itr)] << endl;
                //cout << "Predicted Diff: " << (*(prevDayDiffPred.find(it->second.getName())->second))[it->second.convertDate(*itr)] << endl;

                correct++;
                total++;
            } else if ((*(prevDayDiffPred.find(it->second.getName())->second))[it->second.convertDate(*itr)] < 0.0 &&
                    (*(prevDayDiffActual.find(it->second.getName())->second))[it->second.convertDate(*itr)] < 0.0) {
                //cout << "Correct" << endl;
                //cout << "Actual Diff: " << (*(prevDayDiffActual.find(it->second.getName())->second))[it->second.convertDate(*itr)] << endl;
                //cout << "Predicted Diff: " << (*(prevDayDiffPred.find(it->second.getName())->second))[it->second.convertDate(*itr)] << endl;
                correct++;
                total++;
            } else {
                //cout << "Not correct" << endl;
                total++;
            }
            itr++;

        }
        double percent = (float)correct/total;
        cout << "Stock: " << it->second.getName() << " Percentage: " << percent << endl;
        correct = 0;
        total = 0;
    }

}