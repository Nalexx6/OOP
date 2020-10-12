#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include "note.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toSave_clicked()
{

    Note note{ui->inpNew->toPlainText()};

    QFile file{"data.txt"};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return;

    QTextStream out(&file);
    out << note.text() << "\n";
    file.close();
}
