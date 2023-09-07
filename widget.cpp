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

    connect(ui->lineEdit, &QLineEdit::textChanged, ui->formulaWidget, &FormulaWidget::setFormula);
    connect(ui->formulaWidget, &FormulaWidget::mouseMoved, ui->formulaWidget->getWarningTriangle(), &TriangleWidget::handleMouseMoved);


    //UI---------------------------------
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
    QAction* saveAction = dropdownMenu->addAction("Save");
    saveAction->setStatusTip(tr("Save the file"));
    connect(saveAction, &QAction::triggered, this, &Widget::saveFile);
    QAction* openAction = dropdownMenu->addAction("Open");
    openAction->setStatusTip(tr("Open a file"));
    connect(openAction, &QAction::triggered, this, &Widget::openFile);

    menuButton->setMenu(dropdownMenu);

    //Normali Azioni
    QAction* action1 = toolbar->addAction("Azione 1");
    QAction* action2 = toolbar->addAction("Azione 2");
    QAction* action3 = toolbar->addAction("Azione 3");

    ui->menuLayout->insertWidget(0,toolbar);
    //UI---------------------------------

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

void Widget::keyPressEvent(QKeyEvent* event) {
    // Verifica se è stata premuta la combinazione "Alt+Invio"
    if (event->modifiers() == Qt::SHIFT && event->key() == Qt::Key_Return) {
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


void Widget::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/peppe/Desktop/SalvaFiles", tr("Text files (*.txt)"));
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

void Widget::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "/home/peppe/Desktop/SalvaFiles", tr("Text files (*.txt)"));
    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".txt", Qt::CaseInsensitive)) {
            fileName += ".txt"; // Aggiunge l'estensione .txt se non è già presente
        }
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
