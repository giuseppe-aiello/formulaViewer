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
        }//risolvi -----------
    } else {
        return nullptr;
    }

}

QPoint drawString(QString str, QPoint pos, QPainter& p){

    int valueWidth = p.fontMetrics().horizontalAdvance(str);
    int valueHeight = p.fontMetrics().height();

    p.drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + valueWidth, pos.y() + 4 + valueHeight), str);
    pos = QPoint(pos.x() + valueWidth + 5, pos.y());
    return pos;
}

void SQRTNodeGraphics::draw(QPoint& pos, QPainter& p) {
    //pos non viene modificato, e viene inizializzato posArgument = pos attuale

    pos = QPoint(pos.x() + 12, pos.y());
    QPoint posArgument;

    int valueHeight;

    //FARE FUNZIONE RICORSIVA PER VERIFICARE SE L'ARGOMENTO DI UNA FUNZIUONE CONTIENE UN'ALTRA FUNZIONE
    if(isArgumentFunction(argument[1])!=0){
        posArgument = QPoint(pos.x(), pos.y() + 5);
        argument[1]->draw(posArgument, p);
        //PROBLEMA IN AST.H
        //Se vi è una virgola nell'argomento dell'argomento "sqrt(3, 39393 + sqrt(3, 39939))"
        //viene contato con un argomento del primo sqrt -> CRASH
        this->misure.height = 10 + argument[1]->misure.height;
    } else{
        posArgument = pos;
        argument[1]->draw(posArgument, p);
        this->misure.height =  argument[1]->misure.height;

    }

    //QPoint posArgument2 = posArgument;
    valueHeight = this->misure.height;
    int x = posArgument.x() - pos.x();
    int valueWidth = x; //viene calcolato la larghezza del disegno dell'argomento per poi disegnare la sqrt

    //Appena finirà di disegnare l'argomento, la funzione disegnerà il simbolo della radice
    //a partire da pos (che è invariata fin dall'inizio della funzione.
    NumberNodeGraphics * num = dynamic_cast<NumberNodeGraphics*>(argument[0]);
    p.drawText(pos.x(), pos.y() + 4 + valueHeight / 2, num->number);
    p.drawLine(pos.x(), pos.y() + 4 + valueHeight / 2, pos.x() + 5, pos.y() + 4 + valueHeight);
    p.drawLine(pos.x() + 5, pos.y() + 4 + valueHeight, pos.x() + 10, pos.y() + 1);
    p.drawLine(pos.x() + 10, pos.y() + 1, pos.x() + 14 + valueWidth, pos.y() + 1);

    pos = QPoint(pos.x() + valueWidth + 5, pos.y());
    //posArgument = posArgument2;

}

void BinaryOperatorNodeGraphics::draw(QPoint& pos, QPainter& p) {
    int valueWidth = p.fontMetrics().horizontalAdvance(op);
    this->misure.height = p.fontMetrics().height();

    //misure.width+=valueWidth;

    left->draw(pos, p);
    p.drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + valueWidth, pos.y() + 4 + this->misure.height), op);
    pos = QPoint(pos.x() + valueWidth + 5, pos.y());
    //misure.width+=valueWidth;
    right->draw(pos, p);

}


void NumberNodeGraphics::draw(QPoint& pos, QPainter& p) {

    int valueWidth = p.fontMetrics().horizontalAdvance(number);
    this->misure.height = p.fontMetrics().height();
    //misure.width+=valueWidth;


    p.drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + valueWidth, pos.y() + 4 + misure.height), number);
    pos =QPoint(pos.x() + valueWidth + 5, pos.y());
    //misure.width+= valueWidth;
}


int isArgumentFunction(ASTNodeGraphics *  node){
    int functions = 0;

    if(node == nullptr){
        return functions;
    }

    if(dynamic_cast<FunctionNodeGraphics*>(node)!=nullptr){
        return functions+=1;
    }else if(dynamic_cast<BinaryOperatorNodeGraphics*>(node)!=nullptr){
        BinaryOperatorNodeGraphics * op = static_cast<BinaryOperatorNodeGraphics*>(node);
        return functions = functions + isArgumentFunction(op->getLeft()) + isArgumentFunction(op->getRight());
    } else return functions;

}
