#include "utilities.h"

bool isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/') return true;
    else return false;
}

bool isOperator(std::string val)
{
    if(val == "+" || val == "-" || val == "*" || val == "/") return true;
    else return false;
}

bool isFunction(std::string val)
{
    if(val == "sin" || val == "sqrt" || val == "cos" || val == "square") return true;
    else return false;
}

bool isNumber(std::string val)
{
    return !val.empty() && std::all_of(val.begin(), val.end(), ::isdigit);
}
