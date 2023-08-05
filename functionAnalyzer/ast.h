#ifndef AST_H
#define AST_H

#include "utilities.h"

enum class NodeType {
    Number,
    BinaryOperator,
    Function
};

// Struttura Nodo
class ASTNode {
public:
    virtual ~ASTNode() {}
    virtual NodeType getType() const = 0;
};

class NumberNode : public ASTNode {
public:
    NumberNode(std::string value) : value(value) {}   
    NodeType getType() const override {return NodeType::Number; }

    std::string getValue() const {return value;}

private:
    std::string value;

};

class BinaryOperatorNode : public ASTNode {
public:
    BinaryOperatorNode(std::string operazione, ASTNode * sx, ASTNode* dx)
    : op(operazione), left(sx), right(dx) {}

    NodeType getType() const override {return NodeType::BinaryOperator; }

    std::string getOp() const {return op;}

    ASTNode * getLeft(){
        return left;
    }

    ASTNode * getRight(){
        return right;
    }

private:
    std::string op;
    ASTNode * left;
    ASTNode * right;
};

class FunctionNode : public ASTNode {
public:
    FunctionNode(std::string& nome, std::vector<ASTNode *>& args)
    : name(nome), arguments(args) {}

    NodeType getType() const override {return NodeType::Function; }

    std::string getFunction() const {return name;}

    std::vector<ASTNode *> getArgs() const {return arguments;}


private:
    std::string name;
    std::vector<ASTNode *> arguments;
};

std::string printNode(ASTNode * node);

//Struttura Abstract Syntax Tree
class AST {
public:
    AST(ASTNode * radice) : root(radice) {}
    AST() : root(nullptr) {}
   
    void aggiungiNodo(ASTNode * node){
        root = node;
    }

    std::string printAST(){
        return printNode(this->root);
    }

    ASTNode * getRoot(){
        return this->root;
    }

    //friend void printNode(ASTNode * node);

private:
    ASTNode * root;

};

//FUnzioni per l'analisi sintattica

ASTNode * parseFunction(const std::vector<std::string> tokens, size_t &pos);

ASTNode* parseTokens(std::vector<std::string> tokens, size_t& pos);

AST* buildAST (std::vector<std::string> tokens);

FunctionNode* findMostNestedFunction(ASTNode * node);

void collectFunctions(ASTNode * root, std::vector<FunctionNode *>& functionList);

#endif
