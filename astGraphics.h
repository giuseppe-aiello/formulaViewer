#ifndef ASTGRAPHICS_H
#define ASTGRAPHICS_H

#include <QPainter>
#include <QFont>
#include <QTextDocument>
#include <QStyleOption>
#include <QWidget>
#include "ast.h"

struct sizes{
    int width;
    int height;
};

QPoint drawString(QString str, QPoint pos, QPainter& p);


class ASTNodeGraphics {
public:
    virtual ~ASTNodeGraphics() {}
    virtual void draw(QPoint& pos, QPainter& p) = 0;
    virtual void calculateSizes(sizes& sz, QPainter& p) = 0;
    sizes misure;
};

class NumberNodeGraphics : public ASTNodeGraphics {
public:
    NumberNodeGraphics(std::string value) {
        QString num = QString::fromStdString(value);
        number = num;
    }

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

class SQRTNodeGraphics : public FunctionNodeGraphics {
public:
    SQRTNodeGraphics(std::string function, std::vector<ASTNodeGraphics*> arg) {
        QString n = QString::fromStdString(function);
        name = n;
        argument = arg;
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

    void calculateSizes(sizes& sz,QPainter& p) override;
    void draw(QPoint& pos, QPainter& p) override;
};

ASTNodeGraphics * createNodeGraphicsFromAST(ASTNode * node);

int isArgumentFunction(ASTNodeGraphics *  node);


#endif // ASTGRAPHICS_H
