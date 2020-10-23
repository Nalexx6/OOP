#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QStringListModel>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>
#include <QStackedLayout>
#include <QCloseEvent>

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

    void on_btnArchive_clicked();

    void on_btnNotes_clicked();

    void on_lstArchive_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QVector<Note> data;
    QVector<Note> archive;

    New_note_window new_note_window;

    //main list of notes and archive containers
//    QStringListModel *model;
    QStandardItemModel *main_model;
    QStandardItemModel *arch_model;
    QStackedLayout *lists;

    //private methods
    void load_notes_list(QStandardItemModel *model, QFile& in,  QVector<Note>& list);
    void add_note_to_table(Note& note, QVector<Note>& list ,QStandardItemModel *model);
    void add_note_to_file(const Note& note, QFile& out);
//    void add_note_to_archive(const Note& note);

    //actions with list
    void edit_note(Note& note);
    void delete_note(int data_index, const QModelIndex &index);
    void archive_note(const Note& note);
    int bin_search(const QVector<Note>& list, Date date);

    //
    void closeEvent (QCloseEvent *event);


};
#endif // MAINWINDOW_H
