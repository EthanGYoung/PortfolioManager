/*
 * Fund.h
 *
 *  Created on: Dec 28, 2017
 *      Author: ethanyoung
 */
#include "Stock.h"
#include "Investor.h"
#include <vector>
#include <string>
#include <map>

#ifndef FUND_H_
#define FUND_H_


class Fund {

public:
	Fund();
	virtual ~Fund();
	void addStock(Stock stock);
	bool stockExists(Stock stock);
	Stock getStock(std::string stockName);
	void printStocks(tm Date);
private:
	std::string name;
	std::map<std::string, Stock> stockList;
	std::map<std::string, Investor> investorList;
};

#endif /* FUND_H_ */
