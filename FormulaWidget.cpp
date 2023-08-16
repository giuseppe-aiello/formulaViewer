#include "FormulaWidget.h"

#include "astGraphics.h"


FormulaWidget::FormulaWidget(QWidget* parent) :
    BaseClass(parent)
{
    setMouseTracking(true); // Attiva il tracciamento del mouse per rilevare il movimento anche senza clic
    warningTriangle = new TriangleWidget(); //Crea un istanza di triangolo

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

    //Controllo stringa vuota
    if(testo.isEmpty()){
        return;
    }

    //Controllo spazio finale
    if(testo.endsWith(' ')){
        return;
    }

    //Controllo operatori binari
    if(testo.endsWith('+') || testo.endsWith('-') || testo.endsWith('/') || testo.endsWith('*')){
        warningTriangle->setType(1);
        update();
        return;
    }

    //Controllo parentesi aperta ma non chiusa
    int openParentheses = testo.count('(');
    int closeParentheses = testo.count(')');
    if(openParentheses > closeParentheses){
        warningTriangle->setType(2);
        update();
        return;
    }

    if(testo.endsWith('^')){
        warningTriangle->setType(4);
        update();
        return;
    }

    std::string text = testo.toStdString();
    std::vector<std::string> tokens = tokenizeExpression(text);

    //Controllo ultimo token
    std::string last_token = tokens.back();


    std::regex patternOne(R"((sqrt|frac).*)");
    if(std::regex_match(last_token, patternOne)){
        warningTriangle->setType(3);
        update();
        return;
    }

    this->ast = buildAST(tokens);
    this->graphicsNode = createNodeGraphicsFromAST(ast->getRoot(), this);
    //con update chiamiamo indirettamente l'evento paintEvent, che disegnerà le nostre formule
    //su widget
    warningTriangle->setType(0);
    update();
}


void FormulaWidget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::black);
    QFont normal("StyleNormal", 11);
    p.setFont(normal);
    QPoint formulaPos(5, 50);


    //if(ast!=nullptr) ast->printAST();

    if(graphicsNode!=nullptr) graphicsNode->draw(formulaPos, p);

    if(warningTriangle->getType()!=0){

        switch(warningTriangle->getType()){
        case 1:
            warningTriangle->setPainter(&p);
            warningTriangle->setPos(formulaPos);
            warningTriangle->setWarningMessage("Warning: Missing second operand");
            warningTriangle->paintEvent(event);
            break;
        case 2:
            warningTriangle->setPainter(&p);
            warningTriangle->setPos(formulaPos);
            warningTriangle->setWarningMessage("Warning: Missing closed parenthesis");
            warningTriangle->paintEvent(event);
            break;
        case 3:
            warningTriangle->setPainter(&p);
            warningTriangle->setPos(formulaPos);
            warningTriangle->setWarningMessage("Warning: Incomplete function");
            warningTriangle->paintEvent(event);
            break;
        case 4:
            warningTriangle->setPainter(&p);
            warningTriangle->setPos(formulaPos);
            warningTriangle->setWarningMessage("Warning: Missing degree of monomial");
            warningTriangle->paintEvent(event);
            break;

        }
        }


    }
    //delete this->ast;
    //if(this->ast->getRoot()!=nullptr) delete this->ast;




