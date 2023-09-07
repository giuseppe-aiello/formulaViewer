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
    void saveFile();
    void openFile();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
