//
// Created by Ethan Young on 1/1/18.
//

#include "Backtest.h"
#include <iostream>
using namespace std;


Backtest::Backtest() {

}

Backtest::~Backtest() {
    // TODO Auto-generated destructor stub
}

//Calls algorithm methods to predict dates in Dates using stocks in fund (Predicts all stocks)
//Writes results to the fund (Maybe do 30 day results and 10 day results
void Backtest::runBacktestStocks(Algorithm *algo, std::vector<tm> Dates, Fund *fund) {
    cout << "Running Backtest in backtest" << endl;
    map<std::string, Stock>* stocks = fund->getStockList();
    map<std::string, Stock>::iterator it;

    //Loops through each date
    for (int i = 0; i < (int)Dates.size(); i++) {
        //Loops through each stock
        for ( it = stocks->begin(); it != stocks->end(); it++ )
        {
            //Predict the date passed in for each stocks
            //TODO: Save the prediction and save actuals for each stock
            //algo->predictDate(&(*fund), &(Dates.operator[](i)), &it->second);
        }
    }
}

//Returns true if in same direction
bool Backtest::compareDirection(double prediction, double actual) {
    return ((prediction/actual) > 0);
}

//Returns the difference in magnitude between actual and predicted
double Backtest::compareMagnitude(double prediction, double actual) {
    return actual - prediction;
}

void Backtest::userBacktestMain(Fund *fund) {
    cout << "Running Backtest main in backtest" << endl;
    cout << backtestPrompt;
    Algorithm *al = new Algorithm();
    //tm *dateObj;


    string algo;
    string period;
    string date;

    cout << "Algorithm:" << endl;
    cin >> algo;

    cout << "Period (int):" << endl;
    cin >> period;

    cout << "Starting Date:" << endl;
    cin >> date;

    //Implement when more than one algorithm
    //if (algo == "a");



    vector<string> *fa = new vector<string>();
    fa->push_back("LowPrice");
    fa->push_back("HighPrice");
    fa->push_back("Volume");

    map<string, Stock>* sl = fund->getStockList();
    map<string, Stock>::iterator it;
    vector<tm*>* dates = fund->getDateList();
    vector<tm*>::iterator itr;


    //Loop through all stocks
    for (it = sl->begin(); it != sl->end(); it++) {
        itr = dates->begin() + 50;
        //Loop through each date within the stock
        for (int i = 0; i < 100; i++) {

            double pred = al->predictDate(fund, *itr, fund->getStock(it->second.getName()), fa);

            //Predicts the current date with the stock iterating through
            it->second.addPred("Regression", pred, it->second.convertDate(*itr));
            itr++;
        }
    }
    //itr = dates->begin() + 50;
    //for (int i = 0; i < 2; i++) {
    //    cout << "First Date: " << it->second.convertDate(*itr);
    //    itr++;
    //}


}
