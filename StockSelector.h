/*
 * StockSelector.h
 *
 *  Created on: Dec 20, 2017
 *      Author: ethanyoung
 */
#include "Fund.h"

#ifndef STOCKSELECTOR_H_
#define STOCKSELECTOR_H_
#include <string>

extern char openingMessage[];
extern char responseInvalidInput[];
extern char usernamePrompt[];
extern char passwordPrompt[];
extern char invalidUser[];
extern char managerMain[];
extern char investorMain[];
extern char devMain[];
extern char newUserMain[];
extern std::string stockFilenameDefault;
extern std::string investorFilenameDefault;
extern std::string fundFilenameDefault;
int login();
int investorPrompt();
int managerPrompt();
int developerPrompt();
int newUserPrompt();
bool checkLogin(int mode);
static Fund *fund;

class StockSelector {
public:
	StockSelector();
	virtual ~StockSelector();

};

#endif /* STOCKSELECTOR_H_ */
