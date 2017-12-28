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

class Stock {
public:
	Stock(int Date);
	virtual ~Stock();
	bool buy();
	bool sell();
	float getPriceClose(int Date);
	float getPriceOpen(int Date);
	float getPriceHigh(int Date);
	float getPriceLow(int Date);
	int getVolume(int Date);
	void setPriceClose(int Date, float price);
	void setPriceOpen(int Date, float price);
	void setPriceHigh(int Date, float price);
	void setPriceLow(int Date, float price);
	void setVolume(int Date, int vol);
	//string toString();
private:
	int *priceClose;
	int *priceOpen;
	int *priceHigh;
	int *priceLow;
	int *volume;
	int *purchaseHistory;
	int numDays;
	std::vector<Factor> Factors;

};

#endif /* STOCK_H_ */
