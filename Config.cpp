/*
 * Config.cpp
 *
 *  Created on: Dec 20, 2017
 *      Author: ethanyoung
 */

#include "Config.h"
#include <string>

using namespace std;
/**
 * This class is meant to be any prompts for the user throughout the program.
 * Additionally, there will be formatting for writing to files in here as well.
 *
 * @author Ethan Young
 */
//Opening prompt
char openingMessage[] = "Welcome to the Stock Selector! Are you an investor, portfolio manager, or developer?(Type Corresponding Number)\n"
		"1) Investor\n2) Portfolio Manager\n3) Developer\n4) Create New Account\n0) Exit";
char responseInvalidInput[] = "Invalid Entry. Please repeat or press q to exit.";

//Login prompts
char usernamePrompt[] = "Please enter your username: ";
char passwordPrompt[] = "Please enter your password: ";
char invalidUser[]  = "Username or password not found. Please repeat or type to QUIT to exit.";

//Main Prompts
char managerMain[] = "Welcome to Manager Mode.\n******\nType any of the letters below to enter the corresponding option.\na. View statistics and performance.\nb. Edit/View investors\nc. "
		"Edit/View stocks\nd. Edit/View Algorithm and Simulation settings\ne. Edit/View buying and selling settings\nf. Logout";
char investorMain[] = "Welcome to Investor Mode.\n******\nType any of the letters below to enter the corresponding option.\na. View your stock history and projections.\nb. "
		"Change investment amount.\nc. Edit your investor settings.\nd. Logout";
char devMain[] = "Not implemented yet.";
char newUserMain[] = "Not implemented yet.";

//Input and output filenames
string stockFilenameDefault = "StockData.csv";
string investorFilenameDefault = "InvestorData.csv";
string fundFilenameDefault = "FundData.csv";
char fileDelimDefault = ',';
string defaultFundName = "Portfolio";

Config::Config() {
	// TODO Auto-generated constructor stub

}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

