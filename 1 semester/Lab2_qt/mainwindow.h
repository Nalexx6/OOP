#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QStringListModel>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>
#include <QStackedLayout>
#include <QCloseEvent>
#include <QVector>
#include <QFile>
#include <QShortcut>

#include "note.h"
//#include "date.h"


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

    void on_lstArchive_clicked(const QModelIndex &index);

    void on_btnArchive_clicked();

    void on_btnNotes_clicked();

    void on_btnNew_clicked();

    void on_btnSave_clicked();

    void on_btnSavechng_clicked();

    void on_btnArch_clicked();

    void on_btnUnarch_clicked();

    void on_btnCancel_clicked();

    void on_btnDelete_clicked();

    void on_btnCancelarch_clicked();

    void on_btnSavechngArch_clicked();

    void on_btnDeletearch_clicked();

    void slotShortcutCtrlS();

    void slotShortcutCtrlN();

private:
    Ui::MainWindow *ui;

    QVector<Note> data;
    QVector<Note> archive;

    //main list of notes and archive containers
    QStandardItemModel *main_model;
    QStandardItemModel *arch_model;
    QStackedLayout *lists;

    //private methods
    void load_notes_list(QStandardItemModel *model, QFile& in,  QVector<Note>& list);
    void add_note_to_table(Note& note, QVector<Note>& list ,QStandardItemModel *model);
    void add_note_to_file(const Note& note, QFile& out);
    void closeEvent (QCloseEvent *event);

    //hotkeys
    QShortcut *keyCtrlS;
    QShortcut *keyCtrlN;

    //auxiliary methods or variables
    int bin_search(const QVector<Note>& list, Date date);
    int main_edit_index;
    int arch_edit_index;



};
#endif // MAINWINDOW_H
