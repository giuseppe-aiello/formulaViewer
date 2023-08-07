#ifndef FORMULAWIDGET_H
#define FORMULAWIDGET_H

#include <QRegularExpression>
#include <QPainter>
#include <QTextDocument>
#include <QStyleOption>
#include <QLineEdit>
#include <iostream>
#include <QWidget>

#include "functionAnalyzer/ast.h"
#include "astGraphics.h"
#include "functionAnalyzer/tokenizer.h"

/*
class FormulaItem
{
public:
    explicit FormulaItem(QString value) : m_value(value){}

    static const QString REG_GLOBAL; // Строка регулярного выражения для поиска формулы
    static const QString REG_SQUAREROOT; // Строка регулярного выражения для поиска формулы
    static const QString REG_NORMAL; // Строка регулярного выражения для поиска формулы
    static const QString REG_FORMULA; // Строка регулярного выражения для поиска формулы

    // Метод отрисовки формулы
    QPoint drawSquareRoot(const QPoint& pos, QPainter& p) const;
    QPoint drawNumber(const QPoint& pos, QPainter& p) const;

    QString getValue(){
        return m_value;
    }

    QString m_value; // Значение формулы
};
*/

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
    ASTNodeGraphics * graphicsNode;

};

#endif // FORMULAWIDGET_H
