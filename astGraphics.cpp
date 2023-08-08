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

    //SE CONTIENE DUE ARGOMENTI
    ASTNodeGraphics * first = argument.back();
    argument.pop_back();
    if(isArgumentFunction(first)!=0){
        posArgument = QPoint(pos.x(), pos.y() + 5);
        first->draw(posArgument, p);
        this->misure.height = 10 + first->misure.height;
    } else{
        posArgument = pos;
        first->draw(posArgument, p);
        this->misure.height =  first->misure.height;
    }

    //QPoint posArgument2 = posArgument;
    valueHeight = this->misure.height;
    int x = posArgument.x() - pos.x();
    int valueWidth = x; //viene calcolato la larghezza del disegno dell'argomento per poi disegnare la sqrt

    if(!argument.empty()){
        NumberNodeGraphics * second = dynamic_cast<NumberNodeGraphics *>(argument.back());
        if(second!=nullptr){
            p.drawText(pos.x(), pos.y() + 4 + valueHeight / 2, second->number);
        }
    }
    p.drawLine(pos.x(), pos.y() + 4 + valueHeight / 2, pos.x() + 5, pos.y() + 4 + valueHeight);
    p.drawLine(pos.x() + 5, pos.y() + 4 + valueHeight, pos.x() + 10, pos.y() + 1);
    p.drawLine(pos.x() + 10, pos.y() + 1, pos.x() + 14 + valueWidth, pos.y() + 1);

    pos = QPoint(pos.x() + valueWidth + 5, pos.y());
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
