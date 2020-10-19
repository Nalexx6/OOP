#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QMessageBox>

#include "new_note_window.h"


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

    void on_lstNotes_clicked(const QModelIndex &index);

    void on_btnAddDescr_clicked();

    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Note> data;
    QVector<Note> archive;

    New_note_window new_note_window;

    QStringListModel *model;

    //private methods
    void load_notes_list();
    void add_note_to_table(const QString& title, const Date &date);
    void add_note_to_data(const Note& note);


};
#endif // MAINWINDOW_H
