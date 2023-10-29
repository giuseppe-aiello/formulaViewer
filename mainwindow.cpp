#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget * welcome = ui->stackedWidget->findChild<QWidget*>("welcomePage");
    ui->stackedWidget->insertWidget(0, welcome);
    ui->stackedWidget->insertWidget(1, &_MainWidget);
    QWidget * legend = ui->stackedWidget->findChild<QWidget*>("legendPage");
    ui->stackedWidget->insertWidget(2, legend);

    ui->stackedWidget->setCurrentWidget(welcome);

    setWindowTitle("FormulaViewer");

    QLabel * label = legend->findChild<QLabel*>("label");

    label->setText("Fraction -> frac( NUMERATOR , DENOMINATOR )\n"
                   "\nSquareroot -> sqrt( RADICAND ) OR sqrt( INDEX , RADICAND )\n"
                   "\nPower -> pow( BASE , EXPONENT )\n"
                   "\nMonomial -> 2x / 9y / 12z^3\n"
                   "\nFree text -> text( YOUR_TEXT ) | underscore = space\n"
                   "\nAll functions must be written in lowercase.");


    QLabel * desc = welcome->findChild<QLabel*>("Desc");
    desc->setOpenExternalLinks(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_help_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_startButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_writer_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_legend_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

