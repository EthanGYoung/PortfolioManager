/*
 * Stock.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: ethanyoung
 */

#include "Stock.h"
#include <iostream>


using namespace std;

//Constructor for stock
Stock::Stock(string stockName) {
	numDays = 0;
	name = stockName;
}

// Make sure to free all the memory
Stock::~Stock() {
    // TODO Auto-generated destructor stub
}

// Buys the stock
bool Stock::buy() {
	cout << "Implement buy stock." << endl;
	return true;
}

// Sells the stock
bool Stock::sell() {
	cout << "Implement sell stock." << endl;
	return true;
}

//Converts date to an int for indexing the maps
int Stock::convertDate(tm* Date) {
	return (Date->tm_mon + 1) *1000000 + Date->tm_mday*10000 + Date->tm_year;
}


//Return -1 if factor doesnt exist
float Stock::getFactorValue(std::string factorName, tm* Date) {
	return Factors.at(factorName).getValue(convertDate(Date));
}

void Stock::setFactorValue(std::string factorName, tm* Date, float value) {
	Factors.find(factorName)->second.setValue(convertDate(Date), value);
}

void Stock::addFactor(Factor factor) {
	Factors.insert(pair<string,Factor>(factor.getName(),factor));
}

string Stock::getName() {
	return name;
}


