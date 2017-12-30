/*
 * Fund.cpp
 *
 *  Created on: Dec 28, 2017
 *      Author: ethanyoung
 */

#include "Fund.h"
#include "Stock.h"
#include <string>
#include <iostream>

using namespace std;
/**
 * This class is meant to represent the fund as a whole. This
 * will allow the manager and investors to see statistics regarding
 * the entire find without having to generate it each time from
 * the individual investors.
 *
 * <p>Bugs: (a list of bugs and other problems)
 *
 * @author E
 */
Fund::Fund() {

}

Fund::~Fund() {
	// TODO Auto-generated destructor stub
}

void Fund::addStock(Stock stock) {

	stockList.insert(pair<string,Stock>(stock.getName(),stock));

}

bool Fund::stockExists(Stock stock) {
	map<string, Stock>::iterator it;

	for ( it = stockList.begin(); it != stockList.end(); it++ )
	{
		//Second is the value
		if (it->second.getName() == stock.getName()) {
			return true;
		}
	}

	return false;
}

Stock Fund::getStock(std::string stockName) {
	return stockList.find(stockName)->second;
}

void Fund::printStocks(tm Date) {
	map<string, Stock>::iterator it;


	//cout << "Test";
	for ( it = stockList.begin(); it != stockList.end(); it++ )
	{

		cout << it->second.getName() << ", " << it->second.getFactorValue("Price: Open", Date);

	}
}

