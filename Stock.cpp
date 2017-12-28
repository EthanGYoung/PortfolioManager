/*
 * Stock.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: ethanyoung
 */

#include "Stock.h"
#include "Factor.h"
#include <iostream>
using namespace std;

//Constructor for stock
//Param: Days number of days to look back for array length
Stock::Stock(int days) {
	numDays = days; //Number of days of stock data in the stock object
	priceClose = new int [days]; //Array of closing prices
	priceOpen = new int [days]; //Array of opening prices
	priceHigh = new int [days]; //Array of high prices of each day
	priceLow = new int [days]; //Array of low prices of each day
	volume = new int [days]; //Array of volume traded each day

	//May be different length
	purchaseHistory = new int [days];
	cout << "Not Tested Yet\n";
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

//Getter for priceClose
float Stock::getPriceClose(int Date) {
	return priceClose[Date];
}

//Getter for priceOpen
float Stock::getPriceOpen(int Date) {
	return priceOpen[Date];
}

//Getter for priceHigh
float Stock::getPriceHigh(int Date) {
	return priceHigh[Date];
}

//Getter for priceLow
float Stock::getPriceLow(int Date) {
	return priceLow[Date];
}

//Getter for Volume
int Stock::getVolume(int Date) {
	return volume[Date];
}

//Setter for priceClose
//param price: The price of the close
//param Date: The date of the price to be set
void Stock::setPriceClose(int Date, float price) {
	priceClose[Date] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for price open
//param price: The price of the open
//param Date: The date of the price to be set
void Stock::setPriceOpen(int Date, float price) {
	priceOpen[Date] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for priceHigh
//param price: The price of the High
//param Date: The date of the price to be set
void Stock::setPriceHigh(int Date, float price) {
	priceHigh[Date] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for priceLow
//param price: The price of the Low
//param Date: The date of the price to be set
void Stock::setPriceLow(int Date, float price) {
	priceLow[Date] = price;
	cout << "Set bounds on setting Stock days";
}

//Setter for volume
//param price: The price of the volume
//param Date: The date of the volume to be set
void Stock::setVolume(int Date, int vol) {
	volume[Date] = vol;
	cout << "Set bounds on setting Stock days";
}
