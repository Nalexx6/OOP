#ifndef NEW_NOTE_WINDOW_H
#define NEW_NOTE_WINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

#include "note.h"

namespace Ui {
class New_note_window;
}

class New_note_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit New_note_window(QWidget *parent = nullptr);
    ~New_note_window();

private slots:

    void on_btnSaveandClose_clicked();

private:
    Ui::New_note_window *ui;
};

#endif // NEW_NOTE_WINDOW_H
