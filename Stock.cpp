/*
 * Stock.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: ethanyoung
 */

#include "Stock.h"
#include "Factor.h"
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>

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
/*
//Getter for priceClose
float Stock::getPriceClose(tm Date) {
	return priceClose[convertDate(Date)];
}

//Getter for priceOpen
float Stock::getPriceOpen(tm Date) {
	return priceOpen[convertDate(Date)];
}

//Getter for priceHigh
float Stock::getPriceHigh(tm Date) {
	return priceHigh[convertDate(Date)];
}

//Getter for priceLow
float Stock::getPriceLow(tm Date) {
	return priceLow[convertDate(Date)];
}

//Getter for Volume
int Stock::getVolume(tm Date) {
	return volume[convertDate(Date)];
}

//Setter for priceClose
//param price: The price of the close
//param Date: The date of the price to be set
void Stock::setPriceClose(tm Date, float price) {
	priceClose[convertDate(Date)] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for price open
//param price: The price of the open
//param Date: The date of the price to be set
void Stock::setPriceOpen(tm Date, float price) {
	priceOpen[convertDate(Date)] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for priceHigh
//param price: The price of the High
//param Date: The date of the price to be set
void Stock::setPriceHigh(tm Date, float price) {
	priceHigh[convertDate(Date)] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for priceLow
//param price: The price of the Low
//param Date: The date of the price to be set
void Stock::setPriceLow(tm Date, float price) {
	priceLow[convertDate(Date)] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for volume
//param price: The price of the volume
//param Date: The date of the volume to be set
void Stock::setVolume(tm Date, int vol) {
	volume[convertDate(Date)] = vol;
	cout << "Set bounds on setting Stock days";
}
*/
//Converts date to an int for indexing the maps
int Stock::convertDate(tm Date) {
	return Date.tm_mon *1000000 + Date.tm_mday*10000 + Date.tm_year + 2000;
}


//Return -1 if factor doesnt exist
float Stock::getFactorValue(std::string factorName, tm Date) {
	//TODO: Error here!!! Exits after this line and after call from fund?
	return Factors.find(factorName)->second.getValue(convertDate(Date));
}

void Stock::setFactorValue(std::string factorName, tm Date, float value) {
	Factors.find(factorName)->second.setValue(convertDate(Date), value);
}

void Stock::addFactor(Factor factor) {
	Factors.insert(pair<string,Factor>(factor.getName(),factor)) ;
}

string Stock::getName() {
	return name;
}
