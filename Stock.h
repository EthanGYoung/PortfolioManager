/*
 * Stock.h
 *
 *  Created on: Dec 25, 2017
 *      Author: ethanyoung
 */

#ifndef STOCK_H_
#define STOCK_H_
#include "Factor.h"
#include <vector>
#include <map>
#include <ctime>
#include <string>

class Stock {

public:
	Stock();
	Stock(std::string stockName);
	virtual ~Stock();
	bool buy();
	bool sell();
	float getFactorValue(std::string factorName, tm* Date); //Return -1 if factor doesnt exist
	void setFactorValue(std::string factorName, tm* Date, float value);
	void addFactor(Factor factor);
	std::string getName();
	int convertDate(tm* Date);
    void addPred(std::string algoName, double value, int date);
    std::map<int,double>* getPredList(std::string algoName);
	void addActualDiff(std::string algoName, double actual, double predicted, int date);
private:
	//std::map<int, float> priceClose;
	//std::map<int, float> priceOpen;
	//std::map<int, float> priceHigh;
	//std::map<int, float> priceLow;
	std::map<std::string, std::map<int,double>*> predAlgorithms;
	std::map<std::string, std::map<int,double>*> resultsAlgo;
	//std::map<int, float> purchaseHistory;
	std::map<std::string, Factor> Factors;
	int numDays;
	std::string name;


};

#endif /* STOCK_H_ */
