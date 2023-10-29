#include "ast.h"

//Da aggiornare
void printNode(ASTNode * node){
    if(node->getType() == NodeType::Number) {
        NumberNode * numero = static_cast<NumberNode*>(node);
        std::cout << numero->getValue();
    } else if (node->getType() == NodeType::BinaryOperator) {
        BinaryOperatorNode * operatore = static_cast<BinaryOperatorNode*>(node);
        std::cout << ""; //parentesi
        printNode(operatore->getLeft());
        std::cout << " " << operatore->getOp() << " ";
        printNode(operatore->getRight());
        std::cout << "";
    } else if (node->getType() == NodeType::Function) {
        FunctionNode* funzione = static_cast<FunctionNode*>(node);
        std::cout << funzione->getFunction() << "(";
        size_t tot = funzione->getArgs().size();
        std::vector<ASTNode *> argomenti = funzione->getArgs();
        //std::cout<< "\n";
        //std::cout << tot << " - ARGOMENTI DI " << funzione->getFunction() << std::endl;
        for (size_t i = 0; i < tot; i++)
        {
            if(i>=1) std::cout << " , ";
            printNode(argomenti[i]);
        }
        std::cout << ")";

    } else if(node->getType()==NodeType::Polynomial){
        PolynomialNode * polinomio = static_cast<PolynomialNode*>(node);
        std::cout << polinomio->getValue();
    } else if(node->getType()==NodeType::GenericString){
        GenericStringNode * stringa_generica = static_cast<GenericStringNode*>(node);
        std::cout << stringa_generica->getValue();
    }

}



ASTNode * parseFunction(const std::vector<std::string> tokens, size_t &pos){

    std::string function = tokens[pos];
    std::vector<ASTNode *> args;

    //std::cout << "ARGOMENTI DI " << function << std::endl;

    int openParenthesisCount = 1;

    pos = pos + 2;
    //std::cout << "ALLERT->" << tokens[pos] << std::endl;
    std::vector<std::string> nestedTokens;
    while (pos < tokens.size() && openParenthesisCount>0) { //trova posizione della parentesi chiusa corrispondente
        if(tokens[pos] == "(") {openParenthesisCount++;}
        else if(tokens[pos] == ")") {
            openParenthesisCount--;
        }
        //std::cout << "TOKEN: " << tokens[pos] << std::endl;
        nestedTokens.push_back(tokens[pos]); //Creo un sub-vector di Tokens contenente la sotto-espressione/funzione
        pos++;
    }

    //CASO più ARGOMENTI (BASE ED ESPONENTE)
    if(getIndex(nestedTokens, ",")!=-1){

        size_t totArgs = 0; //= std::count(nestedTokens.begin(), nestedTokens.end(), ",");
        size_t tempPos = 0;

        while(tempPos < nestedTokens.size()){
            if(nestedTokens[tempPos]==","){
                totArgs++;
            }
            else if(isFunction(nestedTokens[tempPos])){
                openParenthesisCount = 1;
                tempPos +=2;
                while (tempPos < nestedTokens.size() && openParenthesisCount>0) {
                    if(nestedTokens[tempPos] == "(") openParenthesisCount++;
                    else if(nestedTokens[tempPos] == ")") openParenthesisCount--;
                    tempPos++;
                }
                if (tempPos < nestedTokens.size() && nestedTokens[tempPos] == ",") {
                    totArgs++; // Conta l'argomento dopo la funzione nidificata
                }
            }
            tempPos++;
        }
        totArgs+=1;

        ASTNode ** ASTNodeArgs = parseMultipleArgs(nestedTokens, (totArgs));

        for (size_t i = 0; i < totArgs; i++)
        {
            args.push_back(ASTNodeArgs[i]);
        }

    }else {
        size_t pos5 = 0;
        ASTNode * argomento = parseTokens(nestedTokens, pos5);
        args.push_back(argomento);
    }
    return new FunctionNode(function, args);
}

ASTNode ** parseMultipleArgs(std::vector<std::string> tokensArgs, size_t totArgs){

    ASTNode ** ASTNodeArgs;
    ASTNodeArgs = new ASTNode * [totArgs];
    size_t pos = 0;

    for (size_t i = 0; i <totArgs; i++)
    {
        std::vector<std::string> singleArg;
        while (pos < tokensArgs.size() && tokensArgs[pos]!=",")
        {
            if(isFunction(tokensArgs[pos])){
                singleArg.push_back(tokensArgs[pos]);
                pos++;
                singleArg.push_back(tokensArgs[pos]);
                pos++;
                int openParenthesisCount = 1;
                while (pos < tokensArgs.size() && openParenthesisCount>0) { //trova posizione della parentesi chiusa corrispondente
                    if(tokensArgs[pos] == "(") openParenthesisCount++;
                    else if(tokensArgs[pos] == ")") openParenthesisCount--;
                    singleArg.push_back(tokensArgs[pos]);
                    pos++;
                }
            }else{
            singleArg.push_back(tokensArgs[pos]);
            pos++;
            }
        }
        size_t newPos=0;
        ASTNodeArgs[i] = parseTokens(singleArg, newPos);
        pos++;
    }
    return ASTNodeArgs;
}


ASTNode* parseTokens(std::vector<std::string> tokens, size_t& pos){

    std::string token = tokens[pos];
    ASTNode * leftOperand = nullptr;
    if(isNumber(token)){
        leftOperand= new NumberNode(token);
        pos++;
    } else if(isFunction(token)){
        if(token!="text"){
        leftOperand = parseFunction(tokens, pos);
        } else { //caso funzione text()
        int openParenthesisCount = 1;
        pos +=2;
        std::string content;
        while (pos < tokens.size() && openParenthesisCount>0) {
            if(tokens[pos] == "(") openParenthesisCount++;
            else if(tokens[pos] == ")") openParenthesisCount--;
            else content+=tokens[pos];
            pos++;
        }
        leftOperand = new FreeTextNode("text", content);
        }
    } else if(isPolynomial(token)){
        leftOperand = new PolynomialNode(token);
        pos++;
    } else {
        leftOperand = new GenericStringNode(token);
        pos++;
    }


    while (pos < tokens.size() && (isOperator(tokens[pos]) || isLineBreak(tokens[pos])))
    {
        std::string op = tokens[pos];
        ASTNode * rightOperand = parseTokens(tokens, ++pos);
        leftOperand = new BinaryOperatorNode(op, leftOperand, rightOperand);
    }
    return leftOperand;
}

AST* buildAST (std::vector<std::string> tokens){
    size_t pos = 0;
    return new AST(parseTokens(tokens, pos));
}

FunctionNode* findMostNestedFunction(ASTNode * node){
    if(node->getType() == NodeType::Function) {

        ASTNode * mostNestedFunction = static_cast<FunctionNode *>(node);
        std::vector<ASTNode *> argomenti = static_cast<FunctionNode *>(node)->getArgs();
        for (size_t i = 0; i < argomenti.size(); i++)
        {
            //std::cout <<"COSA É: " <<static_cast<BinaryOperatorNode*>(argomenti[i])->getOp() << std::endl;
            if(argomenti[i]->getType() == NodeType::Function) mostNestedFunction = findMostNestedFunction(argomenti[i]);
            else if(argomenti[i]->getType() == NodeType::BinaryOperator) mostNestedFunction = findMostNestedFunction(argomenti[i]);
        }
        return static_cast<FunctionNode *>(mostNestedFunction);
    }
    if(node->getType() == NodeType::BinaryOperator){
        BinaryOperatorNode * binaryOpNode = static_cast<BinaryOperatorNode*>(node);
        FunctionNode* leftNestedFunction = findMostNestedFunction(binaryOpNode->getLeft());
        FunctionNode* rightNestedFunction = findMostNestedFunction(binaryOpNode->getRight());

        return leftNestedFunction ? leftNestedFunction : rightNestedFunction;
    }

    return nullptr;

}

void collectFunctions(ASTNode * node, std::vector<FunctionNode *>& functionList){
    if(node->getType() == NodeType::Function){
        FunctionNode * funzione = static_cast<FunctionNode*>(node);
        functionList.push_back(funzione);

        std::vector<ASTNode *> argomenti = funzione->getArgs();
        for (size_t i = 0; i < argomenti.size(); i++)
        {
            if(argomenti[i]->getType() == NodeType::Function || argomenti[i]->getType() == NodeType::BinaryOperator) {
                collectFunctions(argomenti[i], functionList);
            }
        }
    }
    if(node->getType() == NodeType::BinaryOperator){
        BinaryOperatorNode * operatore = static_cast<BinaryOperatorNode*>(node);
        collectFunctions(operatore->getLeft(), functionList);
        collectFunctions(operatore->getRight(), functionList);
    }

}

int getIndex(std::vector<std::string> v, std::string K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {
        int index = it - v.begin();
        return index;
    }
    else {
        // If the element is not
        // present in the vector
        return -1;
    }
}
