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
#include <ctime>
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

	string line; //Line in file
	char delim = ','; //Delimiter in file
	string item; //Item extracted before delimeter
	tm date = tm();

	vector<tm> dateInfo;
	vector<string> stockInfo; //Holds each line in the file

	//Open the input file
	ifstream input (stockFilename);

	//Gets the first line of headers and makes date objects from them
	if (input.good()) {

		getline(input, line);
		stringstream ss(line);

		int i = 0;

		//Separates at the delimiter and inserts into the vector
		while (getline(ss, line, delim)) {
			i++;
			//Does not get the first two places
			if (i < 3) continue;

			date = tm();
			stringstream ss(line);
			//Split at the / to get the date
			if(getline(ss, line, '/')) {
				date.tm_mon = stoi(line)- 1;
			}

			if(getline(ss, line, '/')) {
				date.tm_mday = stoi(line);
			}

			if(getline(ss, line, '/')) {
				date.tm_year = stoi(line);
			}

			dateInfo.push_back(date);

		}
	}
	//Reads and extracts each line of the file to get the stock information
	while (input.good()) {
		//Gets the line in file
		getline(input, line);

		stringstream ss(line);

		//Separates at the delimiter and inserts into the vector
		while (getline(ss, item, delim)) {
			stockInfo.push_back(item);
		}
		//Initialize the stock

	}

	cout << "Stocks\n ";
	for (int i = 0; i < stockInfo.size(); i++) {
		cout << stockInfo.operator[](i) << " ";
	}
	cout << "\nDates\n";

	for (int i = 0; i < dateInfo.size(); i++) {
		cout << to_string(dateInfo.operator[](i).tm_mon) + "/";
		cout << to_string(dateInfo.operator[](i).tm_mday) + "/";
		cout << to_string(dateInfo.operator[](i).tm_year);
		cout << "" << endl;
	}
	cout << "" << endl;

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



