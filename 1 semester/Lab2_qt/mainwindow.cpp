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

    if(data[main_edit_index].title() == ui->ttlEdit->toPlainText() &&
         data[main_edit_index].text() == ui->txtEdit->toPlainText()){

        this->on_btnCancel_clicked();
        return;
    }

    this->main_model->removeRow(main_edit_index);
    data.erase(data.begin() + main_edit_index);

    this->on_btnSave_clicked();

}

void MainWindow::on_btnDelete_clicked()
{

    QMessageBox msgBox;
    msgBox.setText("Are you sure, you want to delete this note?");
    QPushButton *yesBtn = msgBox.addButton(QMessageBox::Yes);
    QPushButton *cancelBtn = msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();

    if (msgBox.clickedButton() == yesBtn) {

        this->main_model->removeRow(main_edit_index);

        QFile res{data[main_edit_index].title() + ".txt"};
        res.remove();

        data.erase(data.begin() + main_edit_index);

        ui->ttlEdit->setText("");
        ui->txtEdit->setText("");
        this->lists->setCurrentWidget(ui->lstNotes);

    } else if (msgBox.clickedButton() == cancelBtn){

       //cancel

    }

}

void MainWindow::on_lstNotes_clicked(const QModelIndex &index)
{
    this->main_edit_index = index.row();

    ui->ttlEdit->setPlainText(data[main_edit_index].title());
    ui->txtEdit->setPlainText(data[main_edit_index].text());

    ui->btnSavechng->show();
    ui->btnDelete->show();

    this->lists->setCurrentWidget(ui->wgtNewnote);

}

void MainWindow::on_lstArchive_clicked(const QModelIndex &index)
{

    this->arch_edit_index = index.row();

    ui->ttlEdit->setPlainText(archive[arch_edit_index].title());
    ui->txtEdit->setPlainText(archive[arch_edit_index].text());

    ui->btnSavechngArch->show();
    ui->btnUnarch->show();
    ui->btnCancelarch->show();
    ui->btnDeletearch->show();


    this->lists->setCurrentWidget(ui->wgtNewnote);

}

void MainWindow::on_btnSavechngArch_clicked()
{

    if(archive[arch_edit_index].title() == ui->ttlEdit->toPlainText() &&
         archive[arch_edit_index].text() == ui->txtEdit->toPlainText()){

        this->on_btnCancelarch_clicked();
        return;
    }

    time_t t;
    time(&t);
    tm* time = localtime(&t);

    this->arch_model->removeRow(arch_edit_index);
    archive.erase(archive.begin() + arch_edit_index);

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

   add_note_to_table(note, archive, arch_model);

   ui->ttlEdit->setText("");
   ui->txtEdit->setText("");
   this->lists->setCurrentWidget(ui->lstArchive);

}

void MainWindow::on_btnUnarch_clicked()
{

}

void MainWindow::on_btnCancelarch_clicked()
{

    ui->ttlEdit->setText("");
    ui->txtEdit->setText("");
    this->lists->setCurrentWidget(ui->lstArchive);

    ui->btnSavechngArch->hide();
    ui->btnUnarch->hide();
    ui->btnCancelarch->hide();
    ui->btnDeletearch->hide();


}


void MainWindow::on_btnDeletearch_clicked()
{

    QMessageBox msgBox;
    msgBox.setText("Are you sure, you want to delete this note?");
    QPushButton *yesBtn = msgBox.addButton(QMessageBox::Yes);
    QPushButton *cancelBtn = msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();

    if (msgBox.clickedButton() == yesBtn) {

        this->arch_model->removeRow(arch_edit_index);

        QFile res{archive[arch_edit_index].title() + ".txt"};
        res.remove();

        archive.erase(archive.begin() + arch_edit_index);

        ui->ttlEdit->setText("");
        ui->txtEdit->setText("");
        this->lists->setCurrentWidget(ui->lstArchive);

    } else if (msgBox.clickedButton() == cancelBtn){

       //cancel

    }

}
