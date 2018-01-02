//
// Created by Ethan Young on 1/1/18.
//

#include "Algorithm.h"

Algorithm::Algorithm() {

}

Algorithm::~Algorithm() {

}

//Dates are chosen by the backtest will predict the Date passed in
//Date: The date to be predicted
//Fund: The fund that is used to predict the data
//Stock:
void Algorithm::predictDate(Fund *fund, tm Date, Stock *st) {
    //TODO: Implement the stock algorithm here
    //Algorithm

    //Model
        //Objective: min sum(currDay over all days in interval) error(day)
        //Constraint: actual(currDay) = A * Factor1(prevDay) + B * Factor2(prevDay) + C * Factor3(prevDay) + error(currDay)
        //Note: Have a constraint for each day in the inteval

    //Get coefficients A, B, C, ..
    //Use to predict the current day of the date passed in
    //Return the predicted value or whether increase or decrease

}