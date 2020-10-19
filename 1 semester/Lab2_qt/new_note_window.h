#ifndef NEW_NOTE_WINDOW_H
#define NEW_NOTE_WINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

#include "note.h"
//#include "mainwindow.h"

namespace Ui {
class New_note_window;
}

class New_note_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit New_note_window(QWidget *parent = nullptr);
    ~New_note_window();

    Note note() const;
    void setNote(const Note &note);


private slots:

    void on_btnCancel_clicked();

    void on_btnSaveDescr_clicked();

private:
    Ui::New_note_window *ui;

    Note _note;

};

#endif // NEW_NOTE_WINDOW_H
