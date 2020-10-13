#include "new_note_window.h"
#include "ui_new_note_window.h"

New_note_window::New_note_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::New_note_window)
{
    ui->setupUi(this);
}

New_note_window::~New_note_window()
{
    delete ui;
}

void New_note_window::on_btnSaveandClose_clicked()
{

    time_t t;
    time(&t);
    tm* time = localtime(&t);
    Date date{ time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
             time->tm_sec, time->tm_min, time->tm_hour};
    Note note{ui->Title_edit->toPlainText() + ".txt", ui->Note_edit->toPlainText(), date};

    QFile file{note.title()};
    if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;

    QTextStream stream(&file);
    stream<< note.text();
    file.close();

    this->hide();
}
