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

void New_note_window::on_btnSaveDescr_clicked()
{

//    Note* note = new Note{ui->titleEdit->toPlainText(), ui->noteEdit->toPlainText(), date};
    this->_note.setText(ui->noteEdit->toPlainText());

    this->hide();

}

Note New_note_window::note() const
{
    return _note;
}

void New_note_window::setNote(const Note &note)
{
    _note = note;
    ui->titleEdit->setText(_note.title());
    ui->noteEdit->setText(_note.text());
}

void New_note_window::on_btnCancel_clicked()
{
//    if(this->_note.text() != ui->noteEdit->toPlainText())

    ui->noteEdit->setText(_note.text());
    this->hide();

}

