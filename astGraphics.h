#ifndef ASTGRAPHICS_H
#define ASTGRAPHICS_H

#include <QPainter>
#include <QFont>
#include <QTextDocument>
#include <QStyleOption>
#include <QWidget>

#include "ast.h"
#include "utilityWidgets.h"

class FormulaWidget;

struct sizes{
    int width=0;
    int height=0;
};


class ASTNodeGraphics {
public:
    virtual ~ASTNodeGraphics() {}
    virtual void draw(QPoint& pos, QPainter& p) = 0;
    virtual void calculateSizes(sizes& sz, QPainter& p) = 0;
    sizes misure;
};
/*
class LineBreakNodeGraphics : public ASTNodeGraphics {
public:
    LineBreakNodeGraphics(){}

    ~LineBreakNodeGraphics() override {
        // delete pointer;
    }

    void calculateSizes(sizes& sz,QPainter& p) override;

    void draw(QPoint& pos, QPainter& p) override;
};*/

class InvalidNodeGraphics : public ASTNodeGraphics {
public:
    InvalidNodeGraphics(std::string value, FormulaWidget * ptr);

    ~InvalidNodeGraphics() override {
        // delete pointer;
    }

    void calculateSizes(sizes& sz,QPainter& p) override;

    void draw(QPoint& pos, QPainter& p) override;

public:
    QString string;

private:
    FormulaWidget * pointer = nullptr;
    RectWidget rect;
};

class NumberNodeGraphics : public ASTNodeGraphics {
public:
    NumberNodeGraphics(std::string value) {
        QString num = QString::fromStdString(value);
        number = num;
    }

    ~NumberNodeGraphics() override {}

    void calculateSizes(sizes& sz,QPainter& p) override;

    void draw(QPoint& pos, QPainter& p) override;

public:
    QString number;
};

class BinaryOperatorNodeGraphics : public ASTNodeGraphics {
public:
    BinaryOperatorNodeGraphics(std::string value, ASTNodeGraphics* sx, ASTNodeGraphics* dx)
        : left(sx), right(dx) {
        QString o = QString::fromStdString(value);
        op = o;
    }

    ~BinaryOperatorNodeGraphics() override {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }

    void draw(QPoint& pos, QPainter& p) override ;

    void calculateSizes(sizes& sz,QPainter& p) override;

    ASTNodeGraphics * getLeft(){
        return left;
    }
    ASTNodeGraphics * getRight(){
        return right;
    }
private:
    QString op;
    ASTNodeGraphics * left;
    ASTNodeGraphics * right;
};

class FunctionNodeGraphics : public ASTNodeGraphics {
public:

    virtual void draw(QPoint& pos, QPainter& p) = 0;

protected:
    QString name;
    std::vector<ASTNodeGraphics*> argument;
};

class PolynomialNodeGraphics : public ASTNodeGraphics {
public:
    PolynomialNodeGraphics(std::string value) {
        QString pol = QString::fromStdString(value);
        polynomial = pol;
    }

    ~PolynomialNodeGraphics() override {}

    void calculateSizes(sizes& sz,QPainter& p) override;

    void draw(QPoint& pos, QPainter& p) override;

public:
    QString polynomial;
};

class SQRTNodeGraphics : public FunctionNodeGraphics {
public:
    SQRTNodeGraphics(std::string function, std::vector<ASTNodeGraphics*> arg) {
        QString n = QString::fromStdString(function);
        name = n;
        argument = arg;
    }
    ~SQRTNodeGraphics() override {
        for(size_t i=0; i<this->argument.size(); i++){
            delete argument[i];
        }
    }
    void calculateSizes(sizes& sz,QPainter& p) override;
    void draw(QPoint& pos, QPainter& p) override;
};

class FractionNodeGraphics : public FunctionNodeGraphics {
public:
    FractionNodeGraphics(std::string function, std::vector<ASTNodeGraphics*> arg) {
        QString n = QString::fromStdString(function);
        name = n;
        argument = arg;
    }
    ~FractionNodeGraphics() override {
        for(size_t i=0; i<this->argument.size(); i++){
            delete argument[i];
        }
    }

    void calculateSizes(sizes& sz,QPainter& p) override;
    void draw(QPoint& pos, QPainter& p) override;
};

class PowerNodeGraphics : public FunctionNodeGraphics {
public:
    PowerNodeGraphics(std::string function, std::vector<ASTNodeGraphics*> arg) {
        QString n = QString::fromStdString(function);
        name = n;
        argument = arg;
    }
    ~PowerNodeGraphics() override {
        for(size_t i=0; i<this->argument.size(); i++){
            delete argument[i];
        }
    }

    void calculateSizes(sizes& sz,QPainter& p) override;
    void draw(QPoint& pos, QPainter& p) override;
};

class FreeTextNodeGraphics : public FunctionNodeGraphics {
public:
    FreeTextNodeGraphics(std::string function, std::string t) {
        functionName = QString::fromStdString(function);
        text = QString::fromStdString(t);
    }
    ~FreeTextNodeGraphics() override {
        for(size_t i=0; i<this->argument.size(); i++){
            delete argument[i];
        }
    }

    void calculateSizes(sizes& sz,QPainter& p) override;
    void draw(QPoint& pos, QPainter& p) override;

private:
    QString functionName;
    QString text;
};


ASTNodeGraphics * createNodeGraphicsFromAST(ASTNode * node, FormulaWidget * ptr);

int isArgumentFunction(ASTNodeGraphics *  node);



#endif // ASTGRAPHICS_H
