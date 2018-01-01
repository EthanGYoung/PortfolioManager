/*
 * Factor.h
 *
 *  Created on: Dec 28, 2017
 *      Author: ethanyoung
 */

#ifndef FACTOR_H_
#define FACTOR_H_
#include <string>
#include <map>

class Factor {

public:
	Factor(std::string *factorName);
	virtual ~Factor();
	void setValue(int index, float value);
	float getValue(int index);
	std::string getName();
private:
	std::string name;
	std::map<int,float> values;
};

#endif /* FACTOR_H_ */
