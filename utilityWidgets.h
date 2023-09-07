#ifndef UTILITYWIDGETS_H
#define UTILITYWIDGETS_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QPolygonF>
#include <QToolTip>
#include <QMouseEvent>

class TriangleWidget : public QWidget {
public:
    TriangleWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    ~TriangleWidget(){}

    void paintEvent(QPaintEvent *){

        topPoint = QPointF(pos.x() + 10 + 10, pos.y() -20);
        leftPoint = QPointF(pos.x() + 10 , pos.y());
        rightPoint= QPointF(pos.x()+ 10 +20, pos.y());

        QPolygonF triangle;
        triangle << topPoint << leftPoint << rightPoint;


            p->setBrush(Qt::yellow);
            p->drawPolygon(triangle);

            QPen pen;
            pen.setColor(Qt::black);
            pen.setWidth(2);
            p->setPen(pen);

            //linea esclamativa
            p->drawLine(pos.x() + 20, pos.y() - 15, pos.x() + 20, pos.y()-7);
            QPointF pointPosition(pos.x() + 20, pos.y() - 3);

            int pointDiameter = 1;

            // punto dell'esclamativo
            QRectF pointRect(pointPosition.x() - pointDiameter / 2.0,
                             pointPosition.y() - pointDiameter / 2.0,
                             pointDiameter, pointDiameter);

            p->drawEllipse(pointRect);

    }
    /*
    void mouseMoveEvent(QMouseEvent *event) override {
        QPointF mousePos = event->pos();

        // Calcola i vertici del triangolo equilatero

        // Controlla se il cursore è sopra il triangolo
        if (pointInTriangle(mousePos, topPoint, leftPoint, rightPoint)) {
            QPoint globalMousePos = mapToGlobal(QPoint(static_cast<int>(mousePos.x()), static_cast<int>(mousePos.y())));
            QToolTip::showText(globalMousePos, "Messaggio di Avviso");
        } else {
            QToolTip::hideText();
        }
    }*/

    void setPainter(QPainter * painter){
        p= painter;
    }
    void setPos(QPoint position){
        pos = position;
    }
    void setType(int warningType){
        type = warningType;
    }

    int getType(){
        return type;
    }

    void setWarningMessage(QString string){
        warningMessage = string;
    }

public slots:

    void handleMouseMoved(const QPoint &position) {

        if(type!=0){
            bool isHovered = pointInTriangle(position, topPoint, leftPoint, rightPoint);

            if (isHovered){
                changeToolTipStyle();
                QToolTip::showText(mapToGlobal(QPoint(static_cast<int>(topPoint.x()), static_cast<int>(topPoint.y() + 40))), this->warningMessage, this, QRect(), -1);
                //QToolTip::setPalette(QApplication::palette()); // Reimposta il palette dei tooltip a quello predefinito

            }else{
                QToolTip::hideText();
            }
        }
    }

protected:

    void changeToolTipStyle() {
        QPalette palette;
        palette.setColor(QPalette::ToolTipBase, Qt::gray); // Cambia il colore dello sfondo
        palette.setColor(QPalette::ToolTipText, Qt::black); // Cambia il colore del testo

        QToolTip::setPalette(palette);
    }

private:
    QPoint pos;
    QPainter *p = nullptr;
    int type;
    QString warningMessage;

    QPointF topPoint;
    QPointF leftPoint;
    QPointF rightPoint;

    bool pointInTriangle(const QPointF &p, const QPointF &p0, const QPointF &p1, const QPointF &p2) {
        //SPIEGAZIONE NEL FILE COOR_BARICENTRICHE
        // Calcola le coordinate baricentriche del punto p rispetto ai vertici del triangolo
        float alpha = ((p1.y() - p2.y()) * (p.x() - p2.x()) + (p2.x() - p1.x()) * (p.y() - p2.y())) /
                      ((p1.y() - p2.y()) * (p0.x() - p2.x()) + (p2.x() - p1.x()) * (p0.y() - p2.y()));

        float beta = ((p2.y() - p0.y()) * (p.x() - p2.x()) + (p0.x() - p2.x()) * (p.y() - p2.y())) /
                     ((p1.y() - p2.y()) * (p0.x() - p2.x()) + (p2.x() - p1.x()) * (p0.y() - p2.y()));

        float gamma = 1.0 - alpha - beta;

        // Verifica se le coordinate baricentriche sono all'interno del triangolo
        return alpha >= 0 && beta >= 0 && gamma >= 0;
        //Se tutte e tre le coordinate baricentriche sono non negative, allora il punto p si trova all'interno
        //del triangolo. Altrimenti, non è all'interno del triangolo.
    }
};


class RectWidget : public QWidget {

public:
    RectWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    ~RectWidget(){}

    void setSettings(QPainter* painter, QPoint position, QString str){
        p= painter;
        pos = position;
        invalidStr = str;

        topLeft = QPoint(pos.x(), pos.y()-p->fontMetrics().height());
        bottomRight = QPoint(pos.x()+p->fontMetrics().horizontalAdvance("invalid"), pos.y());

        beenSet = true;
    }


public slots:

    void handleMouseMoved(const QPoint &position) {

        bool isHovered = pointInRectangle(position, topLeft, bottomRight);
        //std::cout << "BOOL: "<<isHovered <<std::endl;
        if (isHovered){
            changeToolTipStyle();
            QToolTip::showText(mapToGlobal(QPoint(static_cast<int>(topLeft.x()), static_cast<int>(topLeft.y()+50))), "Invalid string: "+invalidStr, this, QRect(), -1);
            //QToolTip::setPalette(QApplication::palette()); // Reimposta il palette dei tooltip a quello predefinito

        }else{
            QToolTip::hideText();
        }
    }


protected:

    void changeToolTipStyle() {
        QPalette palette;
        palette.setColor(QPalette::ToolTipBase, Qt::white); // Cambia il colore dello sfondo
        palette.setColor(QPalette::ToolTipText, Qt::red); // Cambia il colore del testo

        QToolTip::setPalette(palette);
    }

private:

    QPainter *p = nullptr;
    QPoint pos;
    QString invalidStr;

    QPoint topLeft;
    QPoint bottomRight;

    bool beenSet = false;

    bool pointInRectangle(const QPointF &p, const QPointF &topLeft, const QPointF &bottomRight) {
        return p.x() >= topLeft.x() && p.x() <= bottomRight.x() &&
               p.y() >= topLeft.y() && p.y() <= bottomRight.y();
    }
};

#endif // UTILITYWIDGETS_H
