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
#include <ctime>

#ifndef FUND_H_
#define FUND_H_


class Fund {

public:
	Fund();
	virtual ~Fund();
	void addStock(Stock stock);
	void addInvestor(Investor investor);
	bool checkCredentials(string username, string password);
	bool stockExists(Stock stock);
	Stock* getStock(std::string stockName);
	void printStocks(tm Date, std::string factorName);
	void printInvestors(string factorName);
	//void setDateList(std::vector<tm> dl);
private:
	std::string name;
	std::map<std::string, Stock> stockList;
	std::map<std::string, Investor> investorList;
	//std::vector<tm> dateList;
};

#endif /* FUND_H_ */
