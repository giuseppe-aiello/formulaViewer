#ifndef FORMULAWIDGET_H
#define FORMULAWIDGET_H

#include <QPainter>
#include <QStyleOption>
#include <QLineEdit>
#include <iostream>
#include <QWidget>
#include <qmenu.h>

#include "functionAnalyzer/ast.h"
#include "astGraphics.h"
#include "functionAnalyzer/tokenizer.h"


class FormulaWidget : public QWidget
{
    Q_OBJECT
    using BaseClass = QWidget;
public:
    explicit FormulaWidget(QWidget* parent = nullptr);

    AST * ast;


public slots:
    // Слот для установки формулы

    void setFormula();

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    ASTNodeGraphics * graphicsNode = nullptr;

};

#endif // FORMULAWIDGET_H
