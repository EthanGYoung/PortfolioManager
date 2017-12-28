/*
 * Investor.h
 *
 *  Created on: Dec 25, 2017
 *      Author: ethanyoung
 */
#include <string>

using namespace std;
#ifndef INVESTOR_H_
#define INVESTOR_H_

class Investor {
public:
	Investor(string uw, string pw, int Date, float amount);
	virtual ~Investor();
	string getUsername();
	string getPassword();
	float getInitInvest();
	float getInitDate();
	float getCurrInvest();
	int getRiskAmount();
	void setUsername(string uw);
	void setPassword(string pw);
	void setInitDate(int Date);
	void setCurrInvest(float amount);
	void setInitInvest(float amount);
	void setRiskAmount(int amount);

private:
	string username;
	string password;
	float initInvest;
	float initDate;
	float currInvest;
	int riskAmount;

};

#endif /* INVESTOR_H_ */
