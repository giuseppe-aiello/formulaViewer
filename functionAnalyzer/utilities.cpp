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

bool isFunction(std::string val){
    if(val == "pow" || val == "sqrt" || val == "cos" || val == "square" || val == "frac" || val == "text" || val == "sin") return true;
    else return false;
}

bool isNumber(std::string val){
    return !val.empty() && std::all_of(val.begin(), val.end(), ::isdigit);
}

bool isPolynomial(std::string val){
    std::regex polyPattern(R"(\d*[a-z]\^?\d*)");
    
    if(!std::regex_match(val, polyPattern)){
        return false;
    } else return true;
}


bool isLineBreak(std::string val)
{
    if(val == "#") return true;
    else return false;
}
