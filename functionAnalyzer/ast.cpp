#include "ast.h"

std::string printNode(ASTNode * node){
    std::string out;
        if(node->getType() == NodeType::Number) {
            NumberNode * numero = static_cast<NumberNode*>(node);
            out += numero->getValue();
        } else if (node->getType() == NodeType::BinaryOperator) {
            BinaryOperatorNode * operatore = static_cast<BinaryOperatorNode*>(node);
            out += ""; //parentesi
            printNode(operatore->getLeft());
           out += " " + operatore->getOp() + " ";
            printNode(operatore->getRight());
            out += "";
        } else if (node->getType() == NodeType::Function) {
            FunctionNode* funzione = static_cast<FunctionNode*>(node);
            out += funzione->getFunction() + "(";
            size_t tot = funzione->getArgs().size();
            std::vector<ASTNode *> argomenti = funzione->getArgs();
            //std::cout<< "\n";
            //std::cout << tot << " - ARGOMENTI DI " << funzione->getFunction() << std::endl;
            for (size_t i = 0; i < tot; i++)
            {
                printNode(argomenti[i]);
                out += ")";
            }
        }
        return out;

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
            //if(openParenthesisCount>0){
        if(tokens[pos] == "(") {openParenthesisCount++;}
        else if(tokens[pos] == ")") {
            openParenthesisCount--;
        } 
        //std::cout << "TOKEN: " << tokens[pos] << std::endl;
        nestedTokens.push_back(tokens[pos]); //Creo un sub-vector di Tokens contenente la sotto-espressione/funzione
        pos++;
            //}
    }
    size_t pos2 = 0;
    ASTNode * argomento = parseTokens(nestedTokens, pos2);  //
    args.push_back(argomento);

    return new FunctionNode(function, args);
}

// ASTNode * parseNumber(const std::vector<std::string>& tokens, size_t &pos){
//     //size_t startPos= pos;
//     while (pos<tokens.size() && (isNumber(tokens[pos])))
//     {
//         pos ++;
//     }
//     return new NumberNode(tokens[pos]);
// }

// ASTNode * parseOperator(const std::vector<std::string>& tokens, size_t &pos){
//     size_t startPos= pos;
//     while (pos<tokens.size() && (isOperator(tokens[pos])))
//     {
//         pos ++;
//     }
//     return new BinaryOperatorNode(tokens[pos]);
// }

ASTNode* parseTokens(std::vector<std::string> tokens, size_t& pos){

    std::string token = tokens[pos];
    ASTNode * leftOperand;
    if(isNumber(token)){
        leftOperand= new NumberNode(token);
        pos++;
    } else if(isFunction(token)){
        leftOperand = parseFunction(tokens, pos);
    } 
    // else if(isOperator(token)){
    //     std::cout << "ALLERTA" << std::endl;
    //     leftOperand = new NumberNode(token);
    //     pos++;
    // } 
    // else if(token == "("){
    //     leftOperand = parseParenthesis(tokens, pos);
    // }

    while (pos < tokens.size() && isOperator(tokens[pos]))
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

        std::vector<ASTNode *> argomenti = static_cast<FunctionNode *>(node)->getArgs();
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
