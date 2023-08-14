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

    void paintEvent(QPaintEvent *){

        topPoint = QPointF(pos.x() + 10 + 10, pos.y() );
        leftPoint = QPointF(pos.x() + 10 , pos.y() + 20);
        rightPoint= QPointF(pos.x()+ 10 +20, pos.y() + 20);

        QPolygonF triangle;
        triangle << topPoint << leftPoint << rightPoint;


            p->setBrush(Qt::yellow);
            p->drawPolygon(triangle);

            QPen pen;
            pen.setColor(Qt::black);
            pen.setWidth(2);
            p->setPen(pen);

            p->drawLine(pos.x() + 20, pos.y() + 13, pos.x() + 20, pos.y()+5);
            QPointF pointPosition(pos.x() + 20, pos.y() + 17);

            int pointDiameter = 1;

            // Calcola rettangolo dell'ellisse (circonferenza del punto)
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

        if (isHovered) {
            changeToolTipStyle();
            QToolTip::showText(mapToGlobal(QPoint(static_cast<int>(topPoint.x()), static_cast<int>(topPoint.y() + 40))), this->warningMessage, this, QRect(), 3000);
            //QToolTip::setPalette(QApplication::palette()); // Reimposta il palette dei tooltip a quello predefinito

        } else {
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
        // Calcola le coordinate baricentriche del punto p rispetto ai vertici del triangolo
        float alpha = ((p1.y() - p2.y()) * (p.x() - p2.x()) + (p2.x() - p1.x()) * (p.y() - p2.y())) /
                      ((p1.y() - p2.y()) * (p0.x() - p2.x()) + (p2.x() - p1.x()) * (p0.y() - p2.y()));

        float beta = ((p2.y() - p0.y()) * (p.x() - p2.x()) + (p0.x() - p2.x()) * (p.y() - p2.y())) /
                     ((p1.y() - p2.y()) * (p0.x() - p2.x()) + (p2.x() - p1.x()) * (p0.y() - p2.y()));

        float gamma = 1.0 - alpha - beta;

        // Verifica se le coordinate baricentriche sono all'interno del triangolo
        return alpha >= 0 && beta >= 0 && gamma >= 0; // Da personalizzare con l'algoritmo di verifica del punto all'interno del triangolo
    }
};

#endif // UTILITYWIDGETS_H
