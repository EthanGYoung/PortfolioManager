/*
 * DataIO.h
 *
 *  Created on: Dec 28, 2017
 *      Author: ethanyoung
 */

#ifndef DATAIO_H_
#define DATAIO_H_

#include "Stock.h"
#include "Investor.h"
#include "Fund.h"
#include <vector>
#include <string>

class DataIO {
public:
	DataIO();
	DataIO(string stockFilename, string investorFilename, string fundFilename);

	void initializeStocksLocal();
	void initializeInvestorLocal();
	void initializeAllInvestorsLocal();
	void exportInvestorsLocal();
	void exportStocksLocal();
	//Importing the data from computer
	Fund initializeFundLocal();

	//Exporting the Data
	void exportFundLocal();
	virtual ~DataIO();

private:
	Fund fund;
	string stockFilename;
	string investorFilename;
	string fundFilename;

};

#endif /* DATAIO_H_ */
