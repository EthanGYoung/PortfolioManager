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
	//float getPriceClose(tm Date);
	//float getPriceOpen(tm Date);
	//float getPriceHigh(tm Date);
	//float getPriceLow(tm Date);
	//int getVolume(tm Date);
	//void setPriceClose(tm Date, float price);
	//void setPriceOpen(tm Date, float price);
	//void setPriceHigh(tm Date, float price);
	//void setPriceLow(tm Date, float price);
	//void setVolume(tm Date, int vol);
	float getFactorValue(std::string factorName, tm Date); //Return -1 if factor doesnt exist
	void setFactorValue(std::string factorName, tm Date, float value);
	void addFactor(Factor factor);
	std::string getName();
private:
	int convertDate(tm Date);
	//std::map<int, float> priceClose;
	//std::map<int, float> priceOpen;
	//std::map<int, float> priceHigh;
	//std::map<int, float> priceLow;
	//std::map<int, int> volume;
	//std::map<int, float> purchaseHistory;
	std::map<std::string, Factor> Factors;
	int numDays;
	std::string name;


};

#endif /* STOCK_H_ */
