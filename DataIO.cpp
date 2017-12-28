/*
 * DataIO1.cpp
 *
 *  Created on: Dec 28, 2017
 *      Author: ethanyoung
 */

#include "DataIO.h"

#include "Stock.h"
#include "Investor.h"
#include "Fund.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Constructor

//param filenames: These are the filenames for the inputs and outputs of the stocks, investors, and funds
DataIO::DataIO(string stockFile, string investorFile, string fundFile) {
	fund = Fund();
	stockFilename = stockFile;
	investorFilename = investorFile;
	fundFilename = fundFile;

}

//Destructor
DataIO::~DataIO() {

}


/**
 * Initializes all of the stocks from a file and adds to Fund.
 *
 * Format of file:
 * It will be a csv file, which has values separated by columns
 *
 * There will be a header row:
 * Name, Type, Date, Date, Date, Date, ... (Associate an integer and a date object with each date)
 * Ex)
 * AAPL, Price: Close, 10.00, 11.00, 12.00, 11.00
 * AAPL, Price: Open, 10.00, 11.00, 11.00, 10.00
 * AAPL, Factor: Volatility, 10, 11, 4, 3
 * AAPL, Factor: Moving Average, 3, 4, 5, 6
 * GOOG,...
 *
 */
void DataIO::initializeStocksLocal() {
	cout << "Initializing Stocks" << endl;

	string line;
	char delim = ',';
	vector<string> tokens; //Holds each line in the file

	//Open the input file
	ifstream input (stockFilename);

	//Reads and extracts each line of the file to get the stock information
	while (input.good()) {
		getline(input, line);
		stringstream ss;
		ss.str(line);


		string item;

		while (getline(ss, item, delim)) {
			tokens.push_back(item);
		}
		cout << line << endl;
	}

	input.close();
}

//Initializes a single investor
//param investor: The investor that someone is logging in as
//Maybe get rid of and just initialize entire fund every time
//void DataIO::initializeInvestorLocal(Investor investor) {
//	cout << "Initializing Investor: " << investor.getUsername() << endl;
//}

//Initializes all investors
void DataIO::initializeAllInvestorsLocal() {
	cout << "Initializing Investors" << endl;
}

//Initialize the overall fund
Fund DataIO::initializeFundLocal() {
	cout << "Initializing Fund" << endl;

	this->initializeStocksLocal();
	this->initializeAllInvestorsLocal();

	return fund;
}

//Export the investor data to the file
void DataIO::exportInvestorsLocal() {
	cout << "Exporting Investors" << endl;
}

//Export the fund to the data file
void DataIO::exportFundLocal() {
	cout << "Exporting Fund" << endl;
}

//Export the Stocks to data file
void DataIO::exportStocksLocal() { //Needed?
	cout << "Exporting Stocks" << endl;
}



