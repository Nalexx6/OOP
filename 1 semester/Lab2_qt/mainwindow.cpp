#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::MainWindow),
    model(new QStringListModel)
{
    ui->setupUi(this);

    ui->lstNotes->setModel(model);

    load_notes_list();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAddDescr_clicked()
{
    QString title = ui->txtNew_note_ttl->toPlainText();

    if(title == "")
        return;

    new_note_window.setNote(Note(title, new_note_window.note().text(),
                                 Date(1,1,2020, 0,0,0)));
    new_note_window.show();

}

void MainWindow::on_btnSave_clicked()
{
    time_t t;
    time(&t);
    tm* time = localtime(&t);

    Date date{ time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
             time->tm_sec, time->tm_min, time->tm_hour};

    Note note (ui->txtNew_note_ttl->toPlainText(),
               new_note_window.note().text(),
               date);

   data.push_back(note);

   QFile file{note.title() + ".txt"};
   if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
           return;

   QTextStream stream(&file);
   stream<< note.text();
   file.close();

   add_note_to_table(note.title(), note.date());
   add_note_to_data(note);

   ui->txtNew_note_ttl->setText("");
   new_note_window.setNote(Note("", "", Date(1,1,2020, 0,0,0)));

}


void MainWindow::load_notes_list()
{

    QFile in{"data.txt"};
    if (!in.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QString title;
    Date date;
    QTextStream stream(&in);

    while(!in.atEnd()){

//       QString line = in.readLine();

       title = in.readLine();
       date.setDay(in.readLine().toInt());
       date.setMonth(in.readLine().toInt());
       date.setYear(in.readLine().toInt());
       date.setHours(in.readLine().toInt());
       date.setMins(in.readLine().toInt());
       date.setSecs(in.readLine().toInt());

//       std::cout<< "kekw\n";

       add_note_to_table(title, date);

    }

    in.close();

}

void MainWindow::add_note_to_table(const QString& title, const Date &date)
{

    data.push_back(Note(title, "", date));
    QString note_descr = QString("%1 %2/%3/%4 %5:%6:%7").arg(
                title,
                QString::number(date.day()),
                QString::number(date.month()),
                QString::number(date.year()),
                QString::number(date.hours()),
                QString::number(date.mins()),
                QString::number(date.secs()));
    int list_size = model->rowCount();

    model->insertRow(list_size);
    QModelIndex index = model->index(list_size);
    model->setData(index,note_descr);

}

void MainWindow::add_note_to_data(const Note &note)
{

    QFile file{"data.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    bool empty = false;
    if(file.size() == 0){
        empty = true;
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;

    QTextStream stream(&file);

    if(!empty)
        stream << "\n";
    stream << note.title() << "\n" <<
           note.date().day() << "\n" << note.date().month() << "\n" << note.date().year() << "\n"
                         << note.date().hours() << "\n" << note.date().mins() << "\n" << note.date().secs();
    file.close();

}



void MainWindow::on_lstNotes_clicked(const QModelIndex &index)
{

//    QMessageBox::StandardButton reply;
//                reply = QMessageBox::question(this,
//                                              "Choose what do you want to with this note?" );

}



