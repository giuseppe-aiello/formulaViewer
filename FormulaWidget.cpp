#include "FormulaWidget.h"


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
    QFont normal("StyleNormal", 10);
    p.setFont(normal);
    QPoint formulaPos(5, 50);


    //if(ast!=nullptr) ast->printAST();

    if(graphicsNode!=nullptr) graphicsNode->draw(formulaPos, p);


}



