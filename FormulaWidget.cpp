#include "FormulaWidget.h"


//const QString FormulaItem::REG_GLOBAL = "(?<!\\()([-+]?[0-9. ]*)(?!\\))|sqrt\\((?<value>\\d+)\\)";

//const QString FormulaItem::REG_SQUAREROOT = "sqrt\\((?<value>\\d+)\\)";
//const QString FormulaItem::REG_NORMAL = "(?<!\\()([-+]?[0-9. ]*)(?!\\))";
//const QString FormulaItem::REG_FORMULA = "\\((.*)\\)";

/*
QPoint FormulaItem::drawSquareRoot(const QPoint& pos, QPainter& p) const
{

    QString number;

    QRegularExpression reg(FormulaItem::REG_SQUAREROOT);
    QRegularExpressionMatchIterator i = reg.globalMatch(m_value);

    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();
        if(match.hasMatch())
        {
            number.append(match.captured("value"));
        }
    }

    int valueWidth = p.fontMetrics().horizontalAdvance(number);
    int valueHeight = p.fontMetrics().height();

    p.drawLine(pos.x(), 4 + valueHeight / 2, pos.x() + 5, 4 + valueHeight);
    p.drawLine(pos.x() + 5, 4 + valueHeight, pos.x() + 10, pos.y() + 1);
    p.drawLine(pos.x() + 10, pos.y() + 1, pos.x() + 14 + valueWidth, pos.y() + 1);

    p.drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + valueWidth, pos.y() + 4 + valueHeight), number);
    return QPoint(pos.x() + valueWidth + 20, pos.y());
}

QPoint FormulaItem::drawNumber(const QPoint& pos, QPainter& p) const
{
    int valueWidth = p.fontMetrics().horizontalAdvance(m_value);
    int valueHeight = p.fontMetrics().height();

    p.drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + valueWidth, pos.y() + 4 + valueHeight), m_value);
    return QPoint(pos.x() + valueWidth + 20, pos.y());
}
*/
FormulaWidget::FormulaWidget(QWidget* parent) :
    BaseClass(parent)
{
    // Установим цвет фона виджета, по умолчанию он такой же, как в системном оформлении ОС
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}



void FormulaWidget::setFormula()
{

    //QRegularExpression isSquareRoot(FormulaItem::REG_SQUAREROOT);
    //QRegularExpression number(FormulaItem::REG_NORMAL);


    QString testo;
    if(QLineEdit* le = qobject_cast<QLineEdit *>(sender())){
        testo = le->text();
    }
    //tokens.clear();

    std::string text = testo.toStdString();
    std::vector<std::string> tokens = tokenizeExpression(text);

    this->ast = buildAST(tokens);

    this->graphicsNode = createNodeGraphicsFromAST(ast->getRoot());


    //con update chiamiamo indirettamente l'evento paintEvent, che disegnerà le nostre formule
    //su widget

    update();
}


void FormulaWidget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::black);

    QPoint formulaPos(2, 2);

    //if(ast!=nullptr) ast->printAST();

    sizes misure = {0, 0};
    if(graphicsNode!=nullptr) graphicsNode->draw(formulaPos, p);


}



