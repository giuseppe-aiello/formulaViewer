#include "astGraphics.h"

ASTNodeGraphics * createNodeGraphicsFromAST(ASTNode * node){
    if(auto number = dynamic_cast<NumberNode*>(node)){
        return new NumberNodeGraphics(number->getValue());
    }else if(auto operatore = dynamic_cast<BinaryOperatorNode*>(node)){
        std::string op = operatore->getOp();
        ASTNodeGraphics* leftGraphics = createNodeGraphicsFromAST(operatore->getLeft());
        ASTNodeGraphics* rightGraphics = createNodeGraphicsFromAST(operatore->getRight());
        return new BinaryOperatorNodeGraphics(op, leftGraphics, rightGraphics);
    }else if(auto funzione = dynamic_cast<FunctionNode*>(node)){
        std::string functionName = funzione->getFunction();
        if(functionName == "sqrt"){
            std::vector<ASTNodeGraphics*> argumentGraphics;
            for(size_t i=0; i< funzione->getArgs().size(); i++){
                argumentGraphics.push_back(createNodeGraphicsFromAST(funzione->getArgs()[i]));
            }
        return new SQRTNodeGraphics(functionName, argumentGraphics);
        } else if(functionName == "frac"){
            std::vector<ASTNodeGraphics*> argumentGraphics;
            for(size_t i=0; i< funzione->getArgs().size(); i++){
                argumentGraphics.push_back(createNodeGraphicsFromAST(funzione->getArgs()[i]));
            }
        return new FractionNodeGraphics(functionName, argumentGraphics);
        }
    } else if(auto polynomial = dynamic_cast<PolynomialNode*>(node)){
        return new PolynomialNodeGraphics(polynomial->getValue());
    } else if(auto string = dynamic_cast<GenericStringNode*>(node)){
        return new GenericStringNodeGraphics(string->getValue());
    }

}

int isArgumentFunction(ASTNodeGraphics *  node){
    int functions = 0;

    if(node == nullptr){
        return 0;
    }

    if(dynamic_cast<FunctionNodeGraphics*>(node)!=nullptr){
        return 1;
    }else if(dynamic_cast<BinaryOperatorNodeGraphics*>(node)!=nullptr){
        BinaryOperatorNodeGraphics * op = static_cast<BinaryOperatorNodeGraphics*>(node);
        return functions = functions + isArgumentFunction(op->getLeft()) + isArgumentFunction(op->getRight());
    } else return functions;

}

QPoint drawString(QString str, QPoint pos, QPainter& p){

    int valueWidth = p.fontMetrics().horizontalAdvance(str);
    int valueHeight = p.fontMetrics().height();

    p.drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + valueWidth, pos.y() + 4 + valueHeight), str);
    pos = QPoint(pos.x() + valueWidth + 5, pos.y());
    return pos;
}

void NumberNodeGraphics::calculateSizes(sizes& sz, QPainter& p){

    sz.width += p.fontMetrics().horizontalAdvance(this->number, -1);
    if(sz.height < p.fontMetrics().height()-4){
        sz.height= p.fontMetrics().height()-4;
    }
    //std::cout << "NUMBER WIDTH = " << sz.wi
}

void BinaryOperatorNodeGraphics::calculateSizes(sizes& sz, QPainter& p){
    sz.width += p.fontMetrics().horizontalAdvance(this->op, -1) + 10;

    if(left!=nullptr)
        left->calculateSizes(sz, p);

    if(right!=nullptr)
        right->calculateSizes(sz, p);
}

void PolynomialNodeGraphics::calculateSizes(sizes& sz, QPainter& p){

    sz.width += p.fontMetrics().horizontalAdvance(this->polynomial, -1);
    if(sz.height < 7){
        sz.height=7;
    }
}

void GenericStringNodeGraphics::calculateSizes(sizes& sz, QPainter& p){

    sz.width += p.fontMetrics().horizontalAdvance("error", -1);
    if(sz.height < p.fontMetrics().height()-4){
        sz.height= p.fontMetrics().height()-4;
    }
}

void SQRTNodeGraphics::calculateSizes(sizes& sz, QPainter& p){
    sz.width+=12;
    sz.height+=4;

    size_t totArgs = this->argument.size();
    for(size_t i = 0 ; i<totArgs; i++){
        this->argument[i]->calculateSizes(sz, p);
    }
}

void FractionNodeGraphics::calculateSizes(sizes& sz, QPainter& p){

    sizes numerator;
    sizes denominator;

    this->argument[0]->calculateSizes(numerator,p);
    this->argument[1]->calculateSizes(denominator,p);

    if(numerator.width>denominator.width){
        sz.width += numerator.width;
    }
    else sz.width += denominator.width;

    if(sz.height < 25){
        sz.height=25;
    }
}

void NumberNodeGraphics::draw(QPoint& pos, QPainter& p) {

    int valueWidth = p.fontMetrics().horizontalAdvance(number);
    int valueHeight = p.fontMetrics().height();
    //misure.width+=valueWidth;
    this->misure.height = valueHeight;

    p.drawText(pos.x(), pos.y(), number);
    pos =QPoint(pos.x() + valueWidth, pos.y());
    //misure.width+= valueWidth;
}


void BinaryOperatorNodeGraphics::draw(QPoint& pos, QPainter& p) {

    int valueWidth = p.fontMetrics().horizontalAdvance(op);
    int valueHeight = p.fontMetrics().height();
    this->misure.height = valueHeight;

    //misure.width+=valueWidth;

    left->draw(pos, p);
    pos = QPoint(pos.x() + 5, pos.y());
    p.drawText(pos.x(), pos.y(), op);
    pos = QPoint(pos.x() + valueWidth + 5, pos.y());
    //misure.width+=valueWidth;
    right->draw(pos, p);

}

void PolynomialNodeGraphics::draw(QPoint& pos, QPainter& p) {

    if(polynomial.count('^')!=0){
        int valueHeight = p.fontMetrics().height();
        //misure.width+=valueWidth;
        this->misure.height = valueHeight;

        QStringList list = polynomial.split('^');
        //std::cout << "SIZE: " << list.size() << std::endl;
        QString base = list[0];
        QString potenza = list[1];

        int valueWidthBase = p.fontMetrics().horizontalAdvance(base);
        int valueWidthPotenza = p.fontMetrics().horizontalAdvance(potenza);
        int valueWidth = valueWidthBase + valueWidthPotenza;

        p.drawText(pos.x(), pos.y(), base);
        QFont power("StyleNormal", 10);
        p.setFont(power);
        p.drawText(pos.x()+valueWidthBase, pos.y()-valueHeight/2, potenza);
        QFont normal("StyleNormal", 11);
        p.setFont(normal);
        pos =QPoint(pos.x() + valueWidth-3, pos.y());

    } else{
        int valueHeight = p.fontMetrics().height();
        this->misure.height = valueHeight;
        int valueWidth = p.fontMetrics().horizontalAdvance(polynomial);
        p.drawText(pos.x(),pos.y(), polynomial);
        pos =QPoint(pos.x() + valueWidth, pos.y());
    }
    //misure.width+= valueWidth;
}

void GenericStringNodeGraphics::draw(QPoint& pos, QPainter& p) {

    int valueWidth = p.fontMetrics().horizontalAdvance("error");
    int valueHeight = p.fontMetrics().height();
    //misure.width+=valueWidth;
    this->misure.height = valueHeight;

    p.drawText(pos.x(), pos.y(), "error");
    pos =QPoint(pos.x() + valueWidth, pos.y());
    //misure.width+= valueWidth;
}

void SQRTNodeGraphics::draw(QPoint& pos, QPainter& p) {
    //pos non viene modificato, e viene inizializzato posArgument = pos attuale

    pos = QPoint(pos.x(), pos.y());
    QPoint posArgument;

    int valueHeight;
    int valueWidth;

    if(argument.size()==2){
    //SE CONTIENE DUE ARGOMENTI
    ASTNodeGraphics * first = argument[1];

    if(isArgumentFunction(first)!=0){
        posArgument = QPoint(pos.x() + 12, pos.y());
        first->draw(posArgument, p);
        sizes size;
        first->calculateSizes(size, p);
        valueHeight = size.height;
    } else{
        posArgument = QPoint(pos.x() +12, pos.y());
        first->draw(posArgument, p);
        sizes size;
        first->calculateSizes(size, p);
        valueHeight = size.height;
    }
    this->misure.height = valueHeight;

    //QPoint posArgument2 = posArgument;
    int x = posArgument.x() - pos.x();
    valueWidth = x; //viene calcolato la larghezza del disegno dell'argomento per poi disegnare la sqrt

    NumberNodeGraphics * second = dynamic_cast<NumberNodeGraphics *>(argument[0]);
    if(second!=nullptr){
        QFont index("StyleNormal", 9);
        p.setFont(index);
        p.drawText(pos.x() + 1, pos.y() - 3 - valueHeight / 2, second->number);
        QFont normal("StyleNormal", 11);
        p.setFont(normal);
        }
    //SE CONTIENE UN ARGOMENTO
    } else{
        ASTNodeGraphics * first = argument[0];

        if(isArgumentFunction(first)!=0){
        posArgument = QPoint(pos.x() + 12, pos.y());
        first->draw(posArgument, p);
        sizes size;
        first->calculateSizes(size, p);
        valueHeight = size.height;
        } else{
        posArgument = QPoint(pos.x() +12, pos.y());
        first->draw(posArgument, p);
        sizes size;
        first->calculateSizes(size, p);
        valueHeight = size.height;
        }
        this->misure.height = valueHeight;

        int x = posArgument.x() - pos.x();
        valueWidth = x;
    }
    p.drawLine(pos.x(), pos.y() - 4 - valueHeight/2, pos.x() + 5, pos.y());
    p.drawLine(pos.x() + 5, pos.y(), pos.x() + 10, pos.y()- 4 - valueHeight);
    p.drawLine(pos.x() + 10, pos.y() - 4 - valueHeight, pos.x() + 5 + valueWidth, pos.y() - 4 - valueHeight);

    pos = QPoint(pos.x() + valueWidth + 5, pos.y());

}


void FractionNodeGraphics::draw(QPoint& pos, QPainter& p) {

    pos = QPoint(pos.x(), pos.y() - 4);
    QPoint posNumerator;
    QPoint posDenominator;


    ASTNodeGraphics * numerator = argument[0];

    ASTNodeGraphics * denominator = argument[1];

    int valueHeight = 0;

    sizes numSizes;

    numerator->calculateSizes(numSizes, p);

    sizes denSizes;
    denominator->calculateSizes(denSizes, p);

    if(numSizes.width>denSizes.width){

        if(dynamic_cast<FractionNodeGraphics*>(numerator)!=nullptr) posNumerator=  QPoint(pos.x(), pos.y()- numSizes.height);
        else posNumerator = QPoint(pos.x(), pos.y()- 10);
        numerator->draw(posNumerator, p);

        int centeredX= (numSizes.width - denSizes.width) /2;
        posDenominator = QPoint(pos.x() + centeredX, pos.y()+ denSizes.height + 5 );
        denominator->draw(posDenominator, p);

        p.drawLine(pos.x(), pos.y()-2, posNumerator.x(), pos.y()-2);
        pos = QPoint(pos.x() + numSizes.width+3, pos.y()+4);

    }else{ // frac(frac(3993, 3939), frac(33939, 39393))

        posDenominator = QPoint(pos.x(), pos.y()+ denSizes.height + 5);
        denominator->draw(posDenominator, p);

        int centeredX= (denSizes.width - numSizes.width) /2;


        if(dynamic_cast<FractionNodeGraphics*>(numerator)!=nullptr) posNumerator=QPoint(pos.x() + centeredX, pos.y() -numSizes.height);
        else posNumerator = QPoint(pos.x() + centeredX, pos.y()- 10);
        numerator->draw(posNumerator, p);

        p.drawLine(pos.x(),pos.y() - 2, posDenominator.x(), pos.y()-2);
        pos = QPoint(pos.x() + denSizes.width+3, pos.y()+4);

    }

    /*
    int x = posNumerator.x()  - pos.x() ;
    int y = posDenominator.x() - pos.x() ;
    int width;
    if(x>y) {
        width = x;
        p.drawLine(pos.x(), posNumerator.y()+2, posNumerator.x(), posNumerator.y()+2);
        //p.drawRect(pos.x(), pos.y() - 10, posDenominator.x() - pos.x(), denominator->misure.height);
    }
    else{
        width = y;
        p.drawLine(pos.x(), posNumerator.y()+2, posDenominator.x(), posNumerator.y()+2);
    }*/

}

