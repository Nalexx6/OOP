#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "new_note_window.h"
#include "datamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Newnotebtn_clicked();

private:
    Ui::MainWindow *ui;

    QVector<QString> data;
    QVector<QString> archive;

    New_note_window new_note_window;


};
#endif // MAINWINDOW_H
