#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed, ui->formulaWidget, &FormulaWidget::setFormula);
    //ui->lineEdit->setText("29392 + 238832 - 23838");
    //QString testo = QString::fromStdString(ui->formulaWidget->ast->printAST());
    //ui->plainTextEdit->appendPlainText(testo);

}

Widget::~Widget()
{
    delete ui;
}

