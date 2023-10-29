#ifndef AST_H
#define AST_H

#include "utilities.h"

enum class NodeType {
    Number,
    BinaryOperator,
    Function,
    Polynomial,
    GenericString,
    FreeText
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
    ~NumberNode() override {}

    NodeType getType() const override {return NodeType::Number; }

    std::string getValue() const {return value;}

private:
    std::string value;

};

class BinaryOperatorNode : public ASTNode {
public:
    BinaryOperatorNode(std::string operazione, ASTNode * sx, ASTNode* dx)
    : op(operazione), left(sx), right(dx) {}

    ~BinaryOperatorNode() override {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }

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

    ~FunctionNode() override {
        for(size_t i=0; i<this->arguments.size(); i++){
            delete arguments[i];
        }
    }

    NodeType getType() const override {return NodeType::Function; }

    std::string getFunction() const {return name;}

    std::vector<ASTNode *> getArgs() const {return arguments;}


private:
    std::string name;
    std::vector<ASTNode *> arguments;
};

class PolynomialNode : public ASTNode {
public:
    PolynomialNode(std::string value) : value(value) {}
    ~PolynomialNode() override {}

    NodeType getType() const override {return NodeType::Polynomial; }

    std::string getValue() const {return value;}

private:
    std::string value;

};

class GenericStringNode : public ASTNode {
public:
    GenericStringNode(std::string value) : value(value) {}
    ~GenericStringNode() override {}

    NodeType getType() const override {return NodeType::GenericString; }

    std::string getValue() const {return value;}

private:
    std::string value;

};

class FreeTextNode : public ASTNode {
public:
    FreeTextNode(std::string name, std::string content) : function(name), text(content){}
    ~FreeTextNode() override {}

    NodeType getType() const override {return NodeType::FreeText; }

    std::string getFunctionName() const {return function;}
    std::string getText() const {return text;}

private:
    std::string function;
    std::string text;

};

/*
class LineBreakNode : public ASTNode {
public:
    LineBreakNode(std::string value) : value(value) {}
    ~LineBreakNode() override {}

    NodeType getType() const override {return NodeType::LineBreak; }

    std::string getValue() const {return value;}

private:
    std::string value;

};*/

void printNode(ASTNode * node);

//Struttura Abstract Syntax Tree
class AST {
public:
    AST(ASTNode * radice) : root(radice) {}
    AST() : root(nullptr) {}
    ~AST() {
        delete root;
        root = nullptr;
    }
   
    void aggiungiNodo(ASTNode * node){
        root = node;
    }

    void printAST(){
        printNode(this->root);
    }

    ASTNode * getRoot(){
        return this->root;
    }

    //friend void printNode(ASTNode * node);

private:
    ASTNode * root;

};


ASTNode ** parseMultipleArgs(std::vector<std::string> tokensArgs, size_t totArgs);

int getIndex(std::vector<std::string> v, std::string K);

ASTNode * parseFunction(const std::vector<std::string> tokens, size_t &pos);

ASTNode* parseTokens(std::vector<std::string> tokens, size_t& pos);

AST* buildAST (std::vector<std::string> tokens);

FunctionNode* findMostNestedFunction(ASTNode * node);

void collectFunctions(ASTNode * root, std::vector<FunctionNode *>& functionList);

#endif
