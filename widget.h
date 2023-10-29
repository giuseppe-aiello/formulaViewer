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

private slots:
    void on_FRAC_clicked();

    void on_EIGHT_clicked();

    void on_FIVE_clicked();

    void on_FOUR_clicked();

    void on_NINE_clicked();

    void on_ONE_clicked();

    void on_POW_clicked();

    void on_SEVEN_clicked();

    void on_SIX_clicked();

    void on_SQRT_clicked();

    void on_THREE_clicked();

    void on_TWO_clicked();

    void on_ZERO_clicked();

    void on_RESET_clicked();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
