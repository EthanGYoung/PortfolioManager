/*
 * Factor.cpp
 *
 *  Created on: Dec 28, 2017
 *      Author: ethanyoung
 */

#include "Factor.h"
#include <string>

using namespace std;

//This class holds the values for different variables associated with a stock
//EX) Volatility, Moving Average, etc..
Factor::Factor(string *factorName) {
	name = *factorName;

}

Factor::~Factor() {
	// TODO Auto-generated destructor stub
}

void Factor::setValue(int key, float value) {
	values[key] = value;
}

float Factor::getValue(int key) {
	return values[key];
}

string Factor::getName() {
	return name;
}

