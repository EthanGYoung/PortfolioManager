/*
 * StockSelector.cpp
 *
 *  Created on: Dec 20, 2017
 *      Author: ethanyoung
 */

#include "StockSelector.h"
#include "Config.h"
#include <string>
#include <iostream> //For cin and cout
#include <fstream> //For ifstream and ofstream

#include "DataIO.h"
using namespace std;

/**
 * (Write a succinct description of this class here. You should avoid
 * wordiness and redundancy. If necessary, additional paragraphs should
 * be preceded by <p>, the html tag for a new paragraph.)
 *
 * <p>Bugs: (a list of bugs and other problems)
 *
 * @author E
 */

//Constructor
StockSelector::StockSelector() {
	cout << "Constructor called." << endl;

}

//Destructor
StockSelector::~StockSelector() {
	cout << "Destructor called." << endl;
}

/**
 * (Write a succinct description of this method here.  If necessary,
 * additional paragraphs should be preceded by <p>, the html tag for
 * a new paragraph.)
 *
 * @param (parameter name) (Describe the first parameter here)
 * @param (parameter name) (Do the same for each additional parameter)
 * @return (description of the return value)
 */
int main() {
	DataIO IOStream(stockFilenameDefault, investorFilenameDefault, fundFilenameDefault);
	Fund fund = IOStream.initializeFundLocal();

	login();

	return 0;
}

//Displays main message and prompts for credentials (Returns 0 on success, -1 on failure)
//Bug: If in while loop and enter a letter, it goes on infinitely (w was tested)
//Bug: Figure out how to make exit be a q

int login() {
	int response;
	bool valid = false; //Input valid or not

	//Prints opening message and gets user response
	cout << openingMessage << endl;


	while (!valid) {
		//Gets user input
		cin >> response;
		valid = true;

		//Calls appropriate prompt depending on response (TODO: Check return)
		switch (response) {
			//Make this exit later instead of return
			case 0:	return -1;
			case 1: investorPrompt();
					break;
			case 2: managerPrompt();
					break;
			case 3: developerPrompt();
					break;
			case 4: newUserPrompt();
					break;
			default: cout << responseInvalidInput << endl;
					valid = false;
					break;
		}
	}
	return 0;
}

//Handle if Investor
int investorPrompt() {
	char option;

	//Gets user name and password
	if (!checkLogin(1)) return -1;
	cout << investorMain << endl;
	cin >> option;

	return 0;
}

//Handle if Manager (Should initialize all investors and stocks)
int managerPrompt() {
	char option;
	//Gets user name and password
	if (!checkLogin(2)) return -1;

	//Gets the menu option
	cout << managerMain << endl;
	cin >> option;

	return 0;
}

//Handle if Developer (Should initialize all investors and stocks)
int developerPrompt() {
	char option;

	//Gets user name and password
	if (!checkLogin(3)) return -1;

	//Gets the menu option
	cout << devMain << endl;
	cin >> option;

	return 0;
}

//Handle if New User
int newUserPrompt() {
	char option;

	//Gets user name and password
	if (!checkLogin(4)) return -1;
	cout << "New User" << endl;

	//Gets the menu option
	cout << newUserMain << endl;
	cin >> option;

	return 0;
}

//Checks if the user is in the system
//param: prompt - which prompt mode it is in
//Return: Returns true if valid
bool checkLogin(int mode) {
	string username;
	string password;

	//Gets username
	cout << usernamePrompt << endl;
	cin >> username;

	//Gets password
	cout << passwordPrompt << endl;
	cin >> password;

	//Checks if in database

	return true;
}

//Format for each line username:password:initDate:initAmount
bool initializeInvestors(string filename) {
	cout << "Not Tested Yet\n";
	//Declares a variable of type ifstream called inFile
	ifstream inFile;

	//Opens file and checks to see if it was a success
	inFile.open(filename);

	if (inFile.fail()) {
		cout << "Failed to open file\n";
	}


	return true;
}
