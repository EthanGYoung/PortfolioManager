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
#include "Config.h"
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

	cout << "Initializing Stocks\n";


	extern char fileDelimDefault; //Delimiter in file
	string line; //Line in file
	string item; //Item extracted before delimeter

	//Open the input file
	input.open(stockFilename);

	//Reads in the headers to get the dates
	vector<tm*> *dateInfo = getDates(stockFilename
            , fileDelimDefault);

    fund.setDateList(dateInfo);

	int i = 0;
	//Reads and extracts each line of the file to get the stock information
	while (input.good()) {
		i++;

		//Gets the line in file
		getline(input, line);

		stringstream ss(line);

		//Eats headers
		if (i == 1) {
			continue;
		}
		//Gets the name of the stock and create a new instance
		getline(ss, item, fileDelimDefault);
		Stock *currStock;
		Stock st(item);
		currStock = &st;

		//Checks if already added to fund else adds it
		if (!fund.stockExists(*currStock)) {
			fund.addStock(*currStock);
		} else {
			currStock = fund.getStock(currStock->getName());
		}

		//Gets and checks the next field Factor Name and creates a new factor
		getline(ss, item, fileDelimDefault);
		Factor currFactor(&item);

		//Adds factor to list
		currStock->addFactor(currFactor);

		//Sets the value for factor at specified date for stock
		for (int i = 0; i < dateInfo->size(); i++) {
			//Gets the next price
			getline(ss, item, fileDelimDefault);
			currStock->setFactorValue(currFactor.getName(),
					dateInfo->operator[](i), stof(item));
		}

	}

	input.close();
}

//Initializes all investors
void DataIO::initializeAllInvestorsLocal() {
	cout << "Initializing Investors" << endl;

	extern char fileDelimDefault; //Delimiter in file
	string line; //Line in file
	string item;

	//Open the input file
	input.open(investorFilename);

	//Create a vector to hold the factorNamess
	vector<string> vec;
	vector<string> *factorNames = &vec;
	Investor *currInvestor;

	int i = 0;
	//Reads and extracts each line of the file to get the investor information
	while (input.good()) {
        i++;

        //Gets the line in file
        getline(input, line);

        stringstream ss(line);



        //Extracts Headers and factor names
        if (i == 1) {
            //Parses header and gets the names of the factors
            while (getline(ss, item, fileDelimDefault)) {
                if (item == "Username" || item == "Password")
                    continue;
                factorNames->push_back(item);
            }

            continue;
        }

        //Gets the name of the stock and create a new instance
        getline(ss, item, fileDelimDefault);
        string username = item;
        getline(ss, item, fileDelimDefault);
        string password = item;

        //Creates the investor as a pointer
        Investor Inv(username, password);
        currInvestor = &Inv;

        //Initializes factors in fund
        for (int j = 0; j < factorNames->size(); j++) {
            //Creates new factor with correct name and adds to investor
            Factor currFactor(&factorNames->operator[](j));
            currInvestor->addFactor(&currFactor);

            //Gets value and adds to factor
            getline(ss, item, fileDelimDefault);
            currInvestor->setFactorValue(factorNames->operator[](j), stof(item));
        }

        //Adds initialized investor to fund
        fund.addInvestor(*currInvestor);
    }

	input.close();
}

//Initialize the overall fund
Fund * DataIO::initializeFundLocal() {
	cout << "Initializing Fund" << endl;

	this->initializeStocksLocal();
	this->initializeAllInvestorsLocal();

	return &fund;
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

vector<tm*>* DataIO::getDates(string filename, char delim) {
    cout << "Getting Dates." << endl;
	string line;

	vector<tm*> *dates = new vector<tm*>();

	fstream input(filename);

	//Gets the first line of headers and makes date objects from them
	if (input.good()) {

		getline(input, line);
		stringstream ss(line);

		int i = 0;

		//Separates at the delimiter and inserts into the vector
		while (getline(ss, line, delim)) {
			i++;
			//Does not get the first two places
			if (i < 3)
				continue;

			tm *date = new tm();

			stringstream ss(line);
			//Split at the / to get the date
			if (getline(ss, line, '/')) {
				date->tm_mon = stoi(line) - 1;
			}

			if (getline(ss, line, '/')) {
				date->tm_mday = stoi(line);
			}

			if (getline(ss, line, '/')) {
				date->tm_year = stoi(line);
			}

			//Adds date to list
			dates->push_back(date);
		}

	}

	return dates;
}

