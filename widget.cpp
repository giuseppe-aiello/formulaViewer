#include "widget.h"
#include "ui_widget.h"
#include "qpushbutton.h"
#include <QToolBar>
#include <QToolButton>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed, ui->formulaWidget, &FormulaWidget::setFormula);

    ui->menuLayout->setAlignment(Qt::AlignLeft);

    //Toolbar
    QToolBar* toolbar = new QToolBar(this);

    //Menu file
    QToolButton* menuButton = new QToolButton(toolbar);
    menuButton->setText("  File  ");
    menuButton->setPopupMode(QToolButton::InstantPopup);
    toolbar->addWidget(menuButton);
    QMenu* dropdownMenu = new QMenu(this);

    // Crea le azioni del menu
    QAction* actionForFile1 = dropdownMenu->addAction("Azione 1");
    QAction* actionForFile2 = dropdownMenu->addAction("Azione 2");

    menuButton->setMenu(dropdownMenu);

    //Normali Azioni
    QAction* action1 = toolbar->addAction("Azione 1");
    QAction* action2 = toolbar->addAction("Azione 2");
    QAction* action3 = toolbar->addAction("Azione 3");

    ui->menuLayout->insertWidget(0,toolbar);

    /*QMenuBar* menuBar = new QMenuBar(this);
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    //menuBar->setGeometry();
    QMenu *menu = new QMenu("File");
    QAction* action1 = menu->addAction("Azione 1");
    QMenu *menu1 = new QMenu("Prova1");
    QMenu *menu2 = new QMenu("Prova2");
    QMenu *menu3 = new QMenu("Prova3");
    QAction* action2 = menu1->addAction("Azione 1");
    QAction* action3 = menu2->addAction("Azione 1");

    menuBar->addMenu(menu);
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);
    for (QMenu* menus : menuBar->findChildren<QMenu*>()) {
        menus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }*/


    // Aggiungi la barra dei menu alla finestra principale
    //menu->setGeometry(20,20,40,40);
    //ui->horizontalLayout->insertWidget(0,menu);
    //menu->setFixedSize(QSize(50, 25));

}

Widget::~Widget()
{
    delete ui;
}

