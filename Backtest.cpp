//
// Created by Ethan Young on 1/1/18.
// Tested

#include "Backtest.h"
#include <iostream>
#include "Stock.h"

using namespace std;


Backtest::Backtest(Fund *fundEx, int interva, vector<string> *factors, int numDay, tm *predictedDate, bool unknown, int budget, int numPur, double upperLim, double lowerLim) {

    fund = fundEx;
    //Initialize data members
    sl = fund->getStockList();
    dates = fund->getDateList();
    interval = interva; //This is the number of days the algo will look back to predict a date
    numDays = numDay; //This is the number of days that the algo will loop through and predict
    startDate = getDateIndx(predictedDate) -
                numDay; //This is the index into the date list that will serve as the starting point
    factorNames = factors;
    al = new Algorithm(interva, fund, factors, budget, numPur, upperLim, lowerLim);
    predictDate = predictedDate;
    percentCorrect = new map<string, double>();
    increase = new map<string, double>();
    if (unknown) {
        dayUnknown = 0;
    } else {
        dayUnknown = 1;
    }


    map<string, Stock>::iterator it;

    //Initialize actuals and predicted with empty objects, so don't have to worry later about checking if they exist
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

}

//Predicts a date without comparing it to actuals (Since might not have actuals yet)
void Backtest::predictDay() {
    cout << "Start of predict Day" << endl;
    map<string, Stock>::iterator stock;
    vector<tm *>::iterator dt;
    dt = dates->begin() + getDateIndx(predictDate) - 1;

    //Loop through all stocks
    for (stock = sl->begin(); stock != sl->end(); stock++) {

        //Predicts given day and adds to predicted map
        double pred = al->predictDate(predictDate, fund->getStock(stock->second.getName()));
        double prevActual = fund->getStock(stock->second.getName())->getFactorValue("close", *dt);

        (*(predicted.find(stock->second.getName())->second))[stock->second.convertDate(predictDate)] = pred;

        if (pred - prevActual > 0) {
            increase->insert(pair<string, double>(stock->second.getName(), 1));

        } else {
            increase->insert(pair<string, double>(stock->second.getName(), 0));
        }
    }

    cout << "End of predict Day" << endl;

}

//Calls algorithm methods to predict dates in Dates using stocks in fund (Predicts all stocks)
//Writes results to the fund (Maybe do 30 day results and 10 day results
void Backtest::runBacktestStocks() {
    cout << "Running Backtest in backtest" << endl;
    map<string, Stock>::iterator stock;
    vector<tm *>::iterator date;

    //Loop through all stocks
    for (stock = sl->begin(); stock != sl->end(); stock++) {
        date = dates->begin() + startDate - 1; // -1 because use prev day later on, so need to initialize it

        //Loop through each date within the stock //Fix!!
        for (int i = 0; i < numDays + 1 + dayUnknown; i++) {
            //for (int i = 0; i < numDays + dayUnknown; i++) {
            cout << "Running backtest stocks for date" << stock->second.convertDate(*date) << endl;
            //Gets predicted value and actual value for "OpenPrice" for today's date
            double pred = al->predictDate(*date, fund->getStock(stock->second.getName()));

            double actual = fund->getStock(stock->second.getName())->getFactorValue("close", *date);

            //Saves the actual value in the actuals map
            map<int, double> *actList = actuals.find(stock->second.getName())->second;
            (*actList)[stock->second.convertDate(*date)] = actual;

            //Saves predicted value in predicted map and saves the diff between in difference
            (*(predicted.find(stock->second.getName())->second))[stock->second.convertDate(*date)] = pred;

            (*(difference.find(stock->second.getName())->second))[stock->second.convertDate(*date)] = actual - pred;

            //Increments if that date exists
            if (i != numDays + 1) {
                date++;
            }

        }
    }
    cout << "End of backTestStock" << endl;
}

double Backtest::userBacktestMain() {
    cout << "Running Backtest main in backtest" << endl;
    cout << backtestPrompt;

    string algo;
    string period;
    string date;

    cout << "Algorithm:" << endl;
    //cin >> algo;

    cout << "Period (int):" << endl;
    //cin >> period;

    cout << "Starting Date (Default 50 in ):" << endl;
    //cin >> date;

    runBacktestStocks();
    calcPrevDayChange();
    calcPercentCorrect();
    predictDay();

    map<string, double>::iterator itr;

    cout << "Printing" << endl;
    for (itr = percentCorrect->begin(); itr != percentCorrect->end(); itr++) {
        cout << "Stock(" << itr->first << "): " << itr->second << endl;
    }

    double *results = al->selectStockDistribution(percentCorrect, increase);

    //Only runs btResults if day results known
    if (dayUnknown == 1) {
        double result = btResults(results);
        return result;
    }

    return 0.0;
/*
    map<string, double>::iterator itr;

    for (itr = percentCorrect->begin(); itr != percentCorrect->end(); itr++) {
        cout << "Stock(" << itr->first << "): " << itr->second << endl;
    }
*/
}

double Backtest::btResults(double *results) {

    double profit = 0;
    map<string, Stock>::iterator stock;
    int index = getDateIndx(predictDate);
    vector<tm *>::iterator date;
    date = dates->begin() + index;
    int h = 1;

    //Loops through and calculates how much is made in each distribution
    for (stock = sl->begin(); stock != sl->end(); stock++) {
        map<int, double> prevActualList = (*(prevDayDiffActual.find(stock->second.getName())->second));
        map<int, double> actualList = (*(actuals.find(stock->second.getName())->second));

        //Calculates the percent change in the stock
        double actualChange =
                prevActualList[stock->second.convertDate(*date)] / actualList[stock->second.convertDate(*(date - 1))];

        //Profit determined by percent increase * investment
        profit = profit + results[h] * actualChange;
        h++;
    }

    cout << "Total Profit: " << profit << endl;
    return profit;
}

void Backtest::calcPrevDayChange() {
    cout << "Calc Prev Day Change" << endl;
    map<string, Stock>::iterator st;
    vector<tm *>::iterator date;

    //Loop through all stocks
    for (st = sl->begin(); st != sl->end(); st++) {
        date = dates->begin() + startDate;

        //Loop through each date within the stock
        //for (int i = 0; i < numDays + 1; i++) {
        for (int i = 0; i < numDays + dayUnknown; i++) {
            //Gets map corresponding to each stock name from lists
            map<int, double> predList = (*(predicted.find(st->second.getName())->second));
            map<int, double> actualList = (*(actuals.find(st->second.getName())->second));

            //Gets actual and predicted from current and previous date
            double actualCurrDay = actualList[st->second.convertDate(*date)];
            double actualPrevDay = actualList[st->second.convertDate(*(date - 1))];
            double predCurrDay = predList[st->second.convertDate(*date)];

            //Updates the diff maps with the difference between today and prev day for actual and pred
            (*(prevDayDiffActual.find(st->second.getName())->second))[st->second.convertDate(*date)] =
                    actualCurrDay - actualPrevDay;
            (*(prevDayDiffPred.find(st->second.getName())->second))[st->second.convertDate(*date)] =
                    predCurrDay - actualPrevDay;

            date++;
        }
    }
    cout << "End of calcPrevDayChange" << endl;
}

void Backtest::calcPercentCorrect() {
    cout << "CalcPercentCorrect" << endl;
    map<string, Stock>::iterator stock;
    vector<tm *>::iterator date;

    int correct = 0;
    int total = 0;

    //Loop through all stocks
    for (stock = sl->begin(); stock != sl->end(); stock++) {

        date = dates->begin() + startDate;

        //Loop through each date within the stock
        //for (int i = 0; i < numDays + 1; i++) {
        for (int i = 0; i < numDays; i++) {
            //Gets map corresponding to each stock name from lists
            map<int, double> predList = (*(prevDayDiffPred.find(stock->second.getName())->second));
            map<int, double> actualList = (*(prevDayDiffActual.find(stock->second.getName())->second));

            //Increments correct if predicted and actual diff is in same direction (Incrememnts total every time)
            if (predList[stock->second.convertDate(*date)] > 0.0 &&
                actualList[stock->second.convertDate(*date)] > 0.0) {
                correct++;
            } else if (predList[stock->second.convertDate(*date)] < 0.0 &&
                       actualList[stock->second.convertDate(*date)] < 0.0) {
                correct++;
            }
            //cout << "Actual: " << actualList[stock->second.convertDate(*date)] << " For date: "
                 //<< stock->second.convertDate(*date) << endl;

            total++;
            date++;

        }

        //Calculates percent and saves it for later use
        double percent = (float) correct / total;
        percentCorrect->insert(pair<string, double>(stock->second.getName(), percent));
        cout << "Stock: " << stock->second.getName() << " Percentage: " << percent << endl;
        correct = 0;
        total = 0;
    }
    cout << "End of calcPercentCorrect" << endl;

}


int Backtest::getDateIndx(tm *Date) {
    map<string, Stock>::iterator stock;
    stock = sl->begin();
    int date = stock->second.convertDate(Date);
    int index = 0;

    vector<tm *> *dates = fund->getDateList();

    vector<tm *>::iterator it;
    for (it = dates->begin(); it != dates->end(); it++) {
        //Checks for matching date and returns the index to it
        if (stock->second.convertDate(*it) == date) {
            return index;
        } else {
            index++;
        }
    }

    //If the date doesn't exist assumes to be next day
    return dates->size();
}
