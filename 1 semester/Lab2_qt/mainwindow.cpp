#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::MainWindow),
    main_model(new QStandardItemModel),
    arch_model(new QStandardItemModel),
    lists_model(new QStandardItemModel),
    layout(new QStackedLayout),
    keyCtrlS(new QShortcut(this)),
    keyCtrlN(new QShortcut(this))
{
    ui->setupUi(this);

    ui->lstNotes->setModel(main_model);
    ui->lstArchive->setModel(arch_model);
    ui->lstLists->setModel(lists_model);

    this->layout->addWidget(ui->lstNotes);
    this->layout->addWidget(ui->lstArchive);
    this->layout->addWidget(ui->wgtNewnote);

    ui->btnUnarch->hide();
    ui->btnSavechng->hide();
    ui->btnCancelarch->hide();
    ui->btnSavechngArch->hide();
    ui->btnDeletearch->hide();

    this->layout->setCurrentWidget(ui->lstNotes);

    QFile main_data{"data.txt"};
    QFile archive_data{"archive.txt"};
//    main_model->insertColumn(main_model->columnCount());
//    arch_model->insertColumn(arch_model->columnCount());

    load_notes_list(main_model, main_data, data);
    load_notes_list(arch_model, archive_data, archive);
    load_lists();


    keyCtrlS->setKey(Qt::CTRL + Qt::Key_S);
    connect(keyCtrlS, SIGNAL(activated()), this, SLOT(slotShortcutCtrlS()));

    keyCtrlN->setKey(Qt::CTRL + Qt::Key_N);
    connect(keyCtrlN, SIGNAL(activated()), this, SLOT(slotShortcutCtrlN()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnNew_clicked()
{

    ui->btnDelete->hide();
    ui->lblList->hide();

    for(int i = 0; i < lists.size(); i++){


        lists_model->item(i + 1)->setCheckState(Qt::Unchecked);

     }

    this->layout->setCurrentWidget(ui->wgtNewnote);

}

void MainWindow::add_note_to_file(const Note &note, QFile& out)
{

    QSet<QString> _lists = note.lists();
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
                         << note.date().hours() << "\n" << note.date().mins() << "\n" << note.date().secs() <<
                         "\n" << _lists.size();
    for(auto& i: _lists)
        stream << "\n" << i;

    out.close();

}

void MainWindow::load_notes_list(QStandardItemModel *model, QFile& in,  QVector<Note>& list)
{

    if (!in.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

//    qDebug() << "aaaaa\n";
    QString title, text, temp_list;
    int lists_number;
    Date date;
    QTextStream stream(&in);
    QSet <QString> _lists;


    while(!in.atEnd()){

       title = in.readLine();
       title.remove(title.size() - 1, 1);
       date.setDay(in.readLine().toInt());
       date.setMonth(in.readLine().toInt());
       date.setYear(in.readLine().toInt());
       date.setHours(in.readLine().toInt());
       date.setMins(in.readLine().toInt());
       date.setSecs(in.readLine().toInt());
       lists_number = in.readLine().toInt();
       for(int i = 0; i < lists_number; i++){

           temp_list = in.readLine();
           if(!in.atEnd())
           temp_list.remove(temp_list.size() - 1, 1);
           _lists.insert(temp_list);
//           this->lists.insert(temp_list);
       }

       QFile file {title + ".txt"};
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
               return;

       QTextStream temp(&file);

       text = temp.readAll();

       Note note = Note(title, text, date);
       note.setLists(_lists);
       _lists.clear();
       add_note_to_table(note, list, model);

    }

    in.close();

}

void MainWindow::add_note_to_table(Note& note, QVector<Note>& list ,QStandardItemModel *model)
{

    int index = bin_search(list, note.date());
    list.insert(list.begin() + index, note);
//    list.push_back(note);
    QString note_descr = note.title() + "\t";
    QSet<QString> _lists = note.lists();
    if(_lists.size() > 0)
        note_descr += "lists: ";
    for(auto& i: _lists){

        note_descr += i + "; ";

    }

    model->insertRow(index);
    auto item = new QStandardItem(note_descr);
    model->setItem(index, item);

}

int MainWindow::bin_search(const QVector<Note> &list, Date date)
{

    if(list.size() == 0){
        return 0;
    }
    if(list[list.size() - 1].date() >= date){
        return list.size();
    }
    if(list.size() == 1){
        if(list[0].date() < date)
            return 0;
        if(list[0].date() >= date)
            return 1;
    }
    int a = 0, b = list.size() - 1;
    int middle = 0;
    while(a < b){
        middle = (a + b) / 2;
        if(list[middle].date() >= date) {
            a = middle + 1;
            middle = (a + b) / 2;
        } else{
            b = middle;
//                middle = (a + b) / 2;
        }

    }
    return middle;

}

void MainWindow::load_lists()
{


    int index;
    QString new_list = "Add list+";
    index = lists_model->rowCount();
    lists_model->insertRow(index);
    auto item = new QStandardItem(new_list);
    lists_model->setItem(index, item);

    QFile in{"lists.txt"};

    if (!in.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream stream(&in);

    while(!in.atEnd()){

        QString temp_list = in.readLine();
        if(!in.atEnd())
            temp_list.remove(temp_list.size() - 1, 1);

        index = lists_model->rowCount();
        lists_model->insertRow(index);
        auto item = new QStandardItem(temp_list);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        lists_model->setItem(index, item);
        lists.push_back(temp_list);

    }

    in.close();

}

void MainWindow::save_lists()
{

    QFile out{"lists.txt"};
    out.resize(0);

    if (!out.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;

    QTextStream stream(&out);
    for(int i = 0; i < lists.size(); i++){
        if(i > 0)
            stream << "\n" ;
        stream << lists[i];
    }

    out.close();
}

void MainWindow::delete_list(QString &to_delete)
{

    QSet <QString> temp;
    for(int i = 0; i < data.size(); i++){

        temp = data[i].lists();
        if(temp.contains(to_delete)){
            temp.remove(to_delete);
            data[i].setLists(temp);

            QString note_descr = data[i].title() + "\t";
            if(temp.size() > 0)
                note_descr += "lists: ";
            for(auto& i: temp){

                note_descr += i + "; ";

            }

            auto item = new QStandardItem(note_descr);
            main_model->setItem(i, item);
        }


    }

    for(int i = 0; i < archive.size(); i++){

        temp = archive[i].lists();
        if(temp.contains(to_delete)){
            temp.remove(to_delete);
            archive[i].setLists(temp);

            QString note_descr = archive[i].title() + "\t";
            if(temp.size() > 0)
                note_descr += "lists: ";
            for(auto& i: temp){

                note_descr += i + "; ";

            }

            auto item = new QStandardItem(note_descr);
            main_model->setItem(i, item);
        }


    }

}

void MainWindow::on_lstLists_clicked(const QModelIndex &index)
{

    if(index.row() != 0){

        QMessageBox msgBox;
        msgBox.setText("Do you want to delete this list?");
        QPushButton *yesBtn = msgBox.addButton(QMessageBox::Yes);
        QPushButton *cancelBtn = msgBox.addButton(QMessageBox::Cancel);

        msgBox.exec();

        if (msgBox.clickedButton() == yesBtn) {

            delete_list(lists[index.row() - 1] );
            lists.erase(lists.begin() + index.row() - 1);
            lists_model->removeRow(index.row());




        } else if (msgBox.clickedButton() == cancelBtn){

           //cancel

        }
        return;

    }


    QString new_list = QInputDialog::getText(this, tr("New List"),
                                             tr("Enter the title of new list:"), QLineEdit::Normal );

    int size = lists.size();
    lists.push_back(new_list);
    if(size < lists.size()){
        lists_model->insertRow(1);
        auto item = new QStandardItem(new_list);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        lists_model->setItem(1, item);
    }

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

    save_lists();

}

void MainWindow::on_btnArchive_clicked()
{

    this->layout->setCurrentWidget(ui->lstArchive);
    ui->lblList->setText("Archive");
    ui->lblList->show();


}

void MainWindow::on_btnNotes_clicked()
{
    this->layout->setCurrentWidget(ui->lstNotes);
    ui->lblList->setText("Notes");
    ui->lblList->show();

}

void MainWindow::on_btnSave_clicked()
{
    time_t t;
    time(&t);
    tm* time = localtime(&t);


    Date date{ time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
             time->tm_sec, time->tm_min, time->tm_hour};

    QStandardItem* temp;
    QSet <QString> _lists;
    for(int i = 1; i < lists_model->rowCount(); i++){

        temp = lists_model->item(i);
        if(temp->checkState()){

            _lists.insert(lists_model->data(lists_model->indexFromItem(temp)).toString());

        }

    }

    Note note (ui->ttlEdit->toPlainText(),
               ui->txtEdit->toPlainText(),
               date);
    note.setLists(_lists);

   QFile file{note.title() + ".txt"};
   if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
           return;

   QTextStream stream(&file);
   stream<< note.text();
   file.close();

   add_note_to_table(note, data, main_model);

   ui->ttlEdit->setText("");
   ui->txtEdit->setText("");
   this->layout->setCurrentWidget(ui->lstNotes);

   ui->btnDelete->show();
   ui->lblList->show();

}

void MainWindow::on_btnArch_clicked()
{

    main_model->removeRow(main_edit_index);
    add_note_to_table(data[main_edit_index], archive, arch_model);
    data.erase(data.begin() + main_edit_index);


    ui->ttlEdit->setText("");
    ui->txtEdit->setText("");
    ui->lblList->show();
    this->layout->setCurrentWidget(ui->lstNotes);


}

void MainWindow::on_btnCancel_clicked()
{


    ui->ttlEdit->setText("");
    ui->txtEdit->setText("");
    ui->lblList->show();
    this->layout->setCurrentWidget(ui->lstNotes);

}

void MainWindow::on_btnSavechng_clicked()
{

    QStandardItem* temp;
    QSet <QString> _lists;
    for(int i = 1; i < lists_model->rowCount(); i++){

        temp = lists_model->item(i);
        if(temp->checkState()){

            _lists.insert(lists_model->data(lists_model->indexFromItem(temp)).toString());

        }

    }



    if(data[main_edit_index].title() == ui->ttlEdit->toPlainText() &&
         data[main_edit_index].text() == ui->txtEdit->toPlainText() &&
            data[main_edit_index].lists() == _lists){

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
        ui->lblList->show();
        this->layout->setCurrentWidget(ui->lstNotes);

    } else if (msgBox.clickedButton() == cancelBtn){

       //cancel

    }

}

void MainWindow::on_lstNotes_clicked(const QModelIndex &index)
{
    this->main_edit_index = index.row();

    ui->ttlEdit->setPlainText(data[main_edit_index].title());
    ui->txtEdit->setPlainText(data[main_edit_index].text());
    QSet <QString> _lists = data[main_edit_index].lists();

    qDebug() <<  lists.size();
    for(int i = 0; i < this->lists.size(); i++){
        if(_lists.contains(lists[i]))
            lists_model->item(i + 1)->setCheckState(Qt::Checked);
        else
            lists_model->item(i + 1)->setCheckState(Qt::Unchecked);
    }

    ui->btnSavechng->show();
    ui->btnDelete->show();
    ui->lblList->hide();

    this->layout->setCurrentWidget(ui->wgtNewnote);

}

void MainWindow::on_lstArchive_clicked(const QModelIndex &index)
{

    this->arch_edit_index = index.row();

    ui->ttlEdit->setPlainText(archive[arch_edit_index].title());
    ui->txtEdit->setPlainText(archive[arch_edit_index].text());

    QSet <QString> _lists = archive[arch_edit_index].lists();

    qDebug() <<  lists.size();
    for(int i = 0; i < this->lists.size(); i++){
        if(_lists.contains(lists[i]))
            lists_model->item(i + 1)->setCheckState(Qt::Checked);
        else
            lists_model->item(i + 1)->setCheckState(Qt::Unchecked);
    }

//    ui->lstLists->hide();
    ui->btnSavechngArch->show();
    ui->btnUnarch->show();
    ui->btnCancelarch->show();
    ui->btnDeletearch->show();
    ui->lblList->hide();


    this->layout->setCurrentWidget(ui->wgtNewnote);

}

void MainWindow::on_btnSavechngArch_clicked()
{

    QStandardItem* temp;
    QSet <QString> _lists;
    for(int i = 1; i < lists_model->rowCount(); i++){

        temp = lists_model->item(i);
        if(temp->checkState()){

            _lists.insert(lists_model->data(lists_model->indexFromItem(temp)).toString());

        }

    }

    if(archive[arch_edit_index].title() == ui->ttlEdit->toPlainText() &&
         archive[arch_edit_index].text() == ui->txtEdit->toPlainText()
            && archive[arch_edit_index].lists() == _lists){

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
    note.setLists(_lists);

   QFile file{note.title() + ".txt"};
   if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
           return;

   QTextStream stream(&file);
   stream<< note.text();
   file.close();

   add_note_to_table(note, archive, arch_model);


   ui->ttlEdit->setText("");
   ui->txtEdit->setText("");
   ui->lblList->show();
   this->layout->setCurrentWidget(ui->lstArchive);

}

void MainWindow::on_btnUnarch_clicked()
{

    arch_model->removeRow(arch_edit_index);
    add_note_to_table(archive[arch_edit_index], data, main_model);
    archive.erase(archive.begin() + arch_edit_index);


    ui->ttlEdit->setText("");
    ui->txtEdit->setText("");
    ui->lblList->show();
    this->layout->setCurrentWidget(ui->lstArchive);

}

void MainWindow::on_btnCancelarch_clicked()
{

    ui->ttlEdit->setText("");
    ui->txtEdit->setText("");
    ui->lblList->show();
    this->layout->setCurrentWidget(ui->lstArchive);


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
        ui->lblList->show();
        this->layout->setCurrentWidget(ui->lstArchive);

    } else if (msgBox.clickedButton() == cancelBtn){

       //cancel

    }

}

void MainWindow::slotShortcutCtrlS()
{

    if(ui->btnSavechng->isHidden() && ui->btnSavechngArch->isHidden()){
        this->on_btnSave_clicked();
        return;
    }
    if(ui->btnSavechngArch->isHidden()){
        this->on_btnSavechng_clicked();
        return;
    }
    this->on_btnSavechngArch_clicked();
}

void MainWindow::slotShortcutCtrlN()
{

    on_btnNew_clicked();

}




