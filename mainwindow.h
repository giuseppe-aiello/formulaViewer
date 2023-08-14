#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widget.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //Main Menu Buttons
    void on_help_clicked();

    //welcomePage Button
    void on_startButton_clicked();

    void on_writer_clicked();

private:
    Ui::MainWindow *ui;
    Widget _MainWidget;
};

#endif // MAINWINDOW_H
