#ifndef FORMULAWIDGET_H
#define FORMULAWIDGET_H


#include <QPainter>
#include <QStyleOption>
#include <QLineEdit>
#include <iostream>
#include <QWidget>
#include <QMenu>
#include <regex>
#include <qpainterpath.h>

#include "utilityWidgets.h"
//#include <QPolygonF>
//#include <qtooltip.h>

#include "functionAnalyzer/ast.h"
//#include "astGraphics.h"
#include "functionAnalyzer/tokenizer.h"

class ASTNodeGraphics;

class FormulaWidget : public QWidget
{
    Q_OBJECT
    using BaseClass = QWidget;
public:
    explicit FormulaWidget(QWidget* parent = nullptr);

    TriangleWidget * getWarningTriangle(){
        return this->warningTriangle;
    }

public slots:
    void setFormula();

signals:
    void mouseMoved(const QPoint &position);

protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        emit mouseMoved(event->pos());
    }

    virtual void paintEvent(QPaintEvent* event) override;

private:
    ASTNodeGraphics * graphicsNode = nullptr;
    AST * ast = nullptr;

    TriangleWidget * warningTriangle = nullptr;

};

#endif // FORMULAWIDGET_H
