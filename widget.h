#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include "FormulaWidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void saveFile(){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "/home/peppe/Desktop/SalvaFiles", tr("All files (*.*)"));
        if (!fileName.isEmpty()) {
            // Esegui le operazioni desiderate per il salvataggio del file
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                QLineEdit * _lineEdit = findChild<QLineEdit*>("lineEdit");
                out << _lineEdit->text();
                file.close();
            } else {
                QMessageBox::warning(this, tr("Error"), tr("Impossible save the file."));
            }
        }
    }
    void openFile(){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/peppe/Desktop/SalvaFiles", tr("File di testo (*.txt);;All files (*.*"));
        if(!fileName.isEmpty()){
            QFile file (fileName);
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream in(&file);
                QString fileContent = in.readAll();
                file.close();
                QLineEdit * _lineEdit = findChild<QLineEdit*>("lineEdit");
                _lineEdit->setText(fileContent);
            } else{
                QMessageBox::warning(this, tr("Error"), tr("Impossible open the file."));
            }
        }
    }

protected:
    void keyPressEvent(QKeyEvent* event) override {
        // Verifica se è stata premuta la combinazione "Alt+Invio"
        if (event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_Return) {
            // Esegui l'azione di andare a capo (incrementa la posizione verticale)
            QLineEdit * _lineEdit = findChild<QLineEdit*>("lineEdit");
            QString text = _lineEdit->text();
            text = text+"#";
            _lineEdit->setText(text);

            // Richiedi il repaint del widget per riflettere il cambiamento
            FormulaWidget * _formulaWidget = findChild<FormulaWidget *>("formulaWidget");
            _formulaWidget->setFormula();

            // Ignora l'evento per evitare che venga gestito ulteriormente
            event->accept();
            return;
        }
        //BaseClass::keyPressEvent(event);
    }

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
