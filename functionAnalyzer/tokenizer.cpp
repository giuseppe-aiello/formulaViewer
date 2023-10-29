#include "tokenizer.h"

std::vector<std::string> tokenizeExpression(const std::string& expression){
    std::vector<std::string> tokens;
    std::string currentToken;

    for(size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        if(ch == ' '){
            continue; //ignora spazi
        }else if(isOperator(ch)) {
            if(!currentToken.empty()){
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, ch));
        }else if(ch == '(' || ch == ')' || ch == ',') {
            if(!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, ch));
        }else if(ch == '#'){
            //i++;
            //currentToken+=expression[i];
            if(!currentToken.empty()){
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, ch));
        }else{
            //CASO operandi e funzioni
            currentToken += ch; //Costruisce token per operandi e funzioni
        }
    }

    if(!currentToken.empty()) {
        tokens.push_back(currentToken);
    }


    return tokens;
}
