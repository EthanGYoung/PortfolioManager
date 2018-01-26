/*
 * Investor.h
 *
 *  Created on: Dec 25, 2017
 *      Author: ethanyoung
 */
#include <string>
#include <map>
#include "Factor.h"

using namespace std;

#ifndef INVESTOR_H_
#define INVESTOR_H_

extern int defaultInvestorFactorDate;

class Investor {
public:
	Investor(string uw, string pw);
	virtual ~Investor();
	string getUsername();
	string getPassword();
	void addFactor(Factor *factor);
	float getFactorValue(string factorName);
	void setFactorValue(string factorName, float value);
	//float getInitInvest();
	//float getInitDate();
	//float getCurrInvest();
	//int getRiskAmount();
	void setUsername(string uw);
	void setPassword(string pw);
	//void setInitDate(int Date);
	//void setCurrInvest(float amount);
	//void setInitInvest(float amount);
	//void setRiskAmount(int amount);

private:
	string username;
	string password;
	map<string,Factor> Factors;
	//float initInvest;
	//float initDate;
	//float currInvest;
	//int riskAmount;

};

#endif /* INVESTOR_H_ */
