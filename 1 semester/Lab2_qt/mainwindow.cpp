#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::MainWindow),
    main_model(new QStandardItemModel),
    arch_model(new QStandardItemModel),
    lists(new QStackedLayout)
{
    ui->setupUi(this);

    ui->lstNotes->setModel(main_model);
    ui->lstArchive->setModel(arch_model);

    this->lists->addWidget(ui->lstNotes);
    this->lists->addWidget(ui->lstArchive);
    this->lists->addWidget(ui->wgtNewnote);

    ui->btnUnarch->hide();
    ui->btnSavechng->hide();
    ui->btnCancelarch->hide();
    ui->btnSavechngArch->hide();
    ui->btnDeletearch->hide();

    this->lists->setCurrentWidget(ui->lstNotes);

    QFile main_data{"data.txt"};
    QFile archive_data{"archive.txt"};
    load_notes_list(main_model, main_data, data);
    load_notes_list(arch_model, archive_data, archive);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnNew_clicked()
{

    ui->btnDelete->hide();

    this->lists->setCurrentWidget(ui->wgtNewnote);

}

void MainWindow::add_note_to_file(const Note &note, QFile& out)
{

//    QFile file{"data.txt"};
    if (!out.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    bool empty = false;
    if(out.size() == 0){
        empty = true;
    }
    out.close();

    if (!out.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;

    QTextStream stream(&out);

    if(!empty)
        stream << "\n";
    stream << note.title() << "\n" <<
           note.date().day() << "\n" << note.date().month() << "\n" << note.date().year() << "\n"
                         << note.date().hours() << "\n" << note.date().mins() << "\n" << note.date().secs();
    out.close();

}

void MainWindow::load_notes_list(QStandardItemModel *model, QFile& in,  QVector<Note>& list)
{

    if (!in.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

//    qDebug() << "aaaaa\n";
    QString title, text;
    Date date;
    QTextStream stream(&in);

    while(!in.atEnd()){

//       QString line = in.readLine();

       title = in.readLine();
       title.remove(title.size() - 1, 1);
       date.setDay(in.readLine().toInt());
       date.setMonth(in.readLine().toInt());
       date.setYear(in.readLine().toInt());
       date.setHours(in.readLine().toInt());
       date.setMins(in.readLine().toInt());
       date.setSecs(in.readLine().toInt());

//       std::cout<< "kekw\n";
       QFile file {title + ".txt"};
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
               return;

       QTextStream temp(&file);

       text = temp.readAll();

       Note note = Note(title, text, date);
       add_note_to_table(note, list, model);

    }

    in.close();

}

void MainWindow::add_note_to_table(Note& note, QVector<Note>& list ,QStandardItemModel *model)
{

    int index = bin_search(list, note.date());
    list.insert(list.begin() + index, note);
//    list.push_back(note);
    QString note_descr = QString("%1").arg(
                note.title());
//                QString::number(date.day()),
//                QString::number(date.month()),
//                QString::number(date.year()),
//                QString::number(date.hours()),
//                QString::number(date.mins()),
//                QString::number(date.secs()));
//    int list_size = model->rowCount();

    model->insertRow(index);
    auto item = new QStandardItem(note_descr);
//    for(int i = list_size; i > index; i--){
    model->setItem(index, item);
//    }

}

int MainWindow::bin_search(const QVector<Note> &list, Date date)
{

    if(list.size() == 0){
        return 0;
    }
    if(list[list.size() - 1].date() <= date){
        return list.size();
    }
    if(list.size() == 1){
        if(list[0].date() > date)
            return 0;
        if(list[0].date() <= date)
            return 1;
    }
    int a = 0, b = list.size() - 1;
    int middle = 0;
    while(a < b){
        middle = (a + b) / 2;
        if(list[middle].date() <= date) {
            a = middle + 1;
            middle = (a + b) / 2;
        } else{
            b = middle;
//                middle = (a + b) / 2;
        }

    }
    return middle;

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QFile main_file {"data.txt"};
    QFile archive_file {"archive.txt"};

    main_file.resize(0);
    archive_file.resize(0);

    for(auto& i: data){

       add_note_to_file(i, main_file);

    }

    for(auto& i: archive){

       add_note_to_file(i, archive_file);

    }

}

void MainWindow::on_btnArchive_clicked()
{

    this->lists->setCurrentWidget(ui->lstArchive);

}

void MainWindow::on_btnNotes_clicked()
{
    this->lists->setCurrentWidget(ui->lstNotes);
}

void MainWindow::on_btnSave_clicked()
{
    time_t t;
    time(&t);
    tm* time = localtime(&t);

    Date date{ time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
             time->tm_sec, time->tm_min, time->tm_hour};

    Note note (ui->ttlEdit->toPlainText(),
               ui->txtEdit->toPlainText(),
               date);

   QFile file{note.title() + ".txt"};
   if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
           return;

   QTextStream stream(&file);
   stream<< note.text();
   file.close();

   add_note_to_table(note, data, main_model);

   ui->ttlEdit->setText("");
   ui->txtEdit->setText("");
   this->lists->setCurrentWidget(ui->lstNotes);

   ui->btnDelete->show();


}

void MainWindow::on_btnArch_clicked()
{



}

void MainWindow::on_btnCancel_clicked()
{

    ui->ttlEdit->setText("");
    ui->txtEdit->setText("");
    this->lists->setCurrentWidget(ui->lstNotes);

}

void MainWindow::on_btnSavechng_clicked()
{

}

void MainWindow::on_btnDelete_clicked()
{



}

void MainWindow::on_lstNotes_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->ttlEdit->setPlainText(data[row].title());
    ui->txtEdit->setPlainText(data[row].text());

    this->lists->setCurrentWidget(ui->wgtNewnote);




}

void MainWindow::on_lstArchive_clicked(const QModelIndex &index)
{

    //edit, archive, delete, cancel
    QString chosen = arch_model->data(index).toString();

    QMessageBox msgBox;
    msgBox.setText("Choose, what do you want to with this note?");
    QPushButton *editButton = msgBox.addButton(tr("Edit"), QMessageBox::ActionRole);
    QPushButton *deleteButton = msgBox.addButton(tr("Delete"), QMessageBox::ActionRole);
    QPushButton *unarchiveButton = msgBox.addButton(tr("Unarchive"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();

    if (msgBox.clickedButton() == editButton) {

//        Note note;
//        for(auto& i: data){

//            if(i.title() == chosen){
//                edit_note(i);
//                break;
//            }
//        }
    } else if (msgBox.clickedButton() == deleteButton) {
        for(int i = 0; i < archive.size(); i++){

            if(archive[i].title() == chosen){
                arch_model->removeRow(i);
                qDebug() << archive[i].title();
                QFile file(archive[i].title() + ".txt");
                file.remove();
                archive.erase(archive.begin() + i);

                break;
            }

        }
    } else if (msgBox.clickedButton() == unarchiveButton) {
        for(int i = 0; i < archive.size(); i++){

            if(archive[i].title() == chosen){
                arch_model->removeRow(i);
//                qDebug() << data[i].title();
                add_note_to_table(archive[i], data, main_model);
                archive.erase(archive.begin() + i);
                break;
            }

        }
    } else if (msgBox.clickedButton() == cancelButton) {
        // cancel
    }

}

void MainWindow::on_btnSavechngArch_clicked()
{

}

void MainWindow::on_bthUnarch_clicked()
{

}

void MainWindow::on_bthCancelarch_clicked()
{

    ui->ttlEdit->setText("");
    ui->txtEdit->setText("");
    this->lists->setCurrentWidget(ui->lstArchive);

}


void MainWindow::on_btnDeletearch_clicked()
{

}
