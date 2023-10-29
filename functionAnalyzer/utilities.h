#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <regex>

bool isOperator(char ch);

bool isOperator(std::string val);

bool isFunction(std::string val);

bool isNumber(std::string val);

bool isPolynomial(std::string val);

bool isLineBreak(std::string val);

#endif
