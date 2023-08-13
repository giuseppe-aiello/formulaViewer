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

