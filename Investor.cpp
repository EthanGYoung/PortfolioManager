/*
 * Investor.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: ethanyoung
 */

#include "Investor.h"
#include <iostream>
using namespace std;
//Constructor
Investor::Investor(string uw, string pw, int Date, float amount) {
	username = uw; //Username of the investor
	password = pw; //Password of the investor
	initInvest = amount; // The amount the investor has put in the fund
	initDate = Date; // The date they began
	currInvest = 0; // The amount their money is currently worth
	riskAmount = 0; // The amount of risk that they wanted
	cout << "Not Tested Yet\n";

}

Investor::~Investor() {
	// TODO Auto-generated destructor stub
}

// Get the username for the investor
string Investor::getUsername() {
	cout << "Create the file that holds investor info" << endl;
	return username;
}

// Get the password for the investor
string Investor::getPassword() {
	cout << "Create the file that holds investor info" << endl;
	return password;
}

// Get the amount the investor has invested
float Investor::getInitInvest() {
	cout << "Create the file that holds investor info" << endl;
	return initInvest;
}

// Get the initial date of the invesotr signup
float Investor::getInitDate() {
	cout << "Create the file that holds investor info" << endl;
	return initDate;
}

// Get the current amount that the investor's money is worth
float Investor::getCurrInvest() {
	cout << "Create the file that holds investor info" << endl;
	return currInvest;
}

// Gets the amount of risk that the investor has in their settings
int Investor::getRiskAmount() {
	cout << "Create the file that holds investor info" << endl;
	return riskAmount;
}

//Set the username
//Param uw: the username as a string
void Investor::setUsername(string uw) {
	cout << "Create the file that holds investor info" << endl;
	username = uw;
}

//Set the passwrod
//param pw: The password as a string
void Investor::setPassword(string pw) {
	cout << "Create the file that holds investor info" << endl;
	password = pw;
}

//Sets the initial date that they were inputed into the system
//param Date: The date
void Investor::setInitDate(int Date) {
	cout << "Create the file that holds investor info" << endl;
	initDate = Date;
}

//Set the current amount that their money is worth
//para amount: The amount that they are worth in the fund
void Investor::setCurrInvest(float amount) {
	cout << "Create the file that holds investor info" << endl;
	currInvest = amount;
}

//Set the amount that they initially invested money on the fund
//param amount: The amount they initially invested
void Investor::setInitInvest(float amount) {
	cout << "Create the file that holds investor info" << endl;
	initInvest = amount;
}

//Set the amount of risk that the user wants
//param amount: The amount that the user wants to risk
void Investor::setRiskAmount(int amount) {
	cout << "Create the file that holds investor info" << endl;
	riskAmount = amount;
}
