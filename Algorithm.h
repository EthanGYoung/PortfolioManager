//
// Created by Ethan Young on 1/1/18.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <ctime>
#include "Fund.h"


class Algorithm {
public:
    Algorithm();
    virtual ~Algorithm();
    double predictDate(Fund *fund, tm *Date, Stock *st, vector<string> *faName);
    int getDateIndex(tm* Date, Stock *st, Fund *fund);
    double getPrediction(double result[], vector<string> *faName, Stock *stk, int date, vector<tm*> *dates);
};


#endif //ALGORITHM_H
