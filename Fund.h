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

#ifndef FUND_H_
#define FUND_H_


class Fund {
public:
	Fund();
	virtual ~Fund();
private:
	string name;
	std::vector<Stock> stockList;
	std::vector<Investor> investorList;
};

#endif /* FUND_H_ */
