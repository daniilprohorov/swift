#include <QStandardItemModel>
#include <QtSql>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->build->addItem("Весна", 0);
    ui->dateTimeEdit->setDate(QDate::currentDate());

/**************************************************************
 *                          Base of Data
 *************************************************************/

    qDebug() << QSqlDatabase::drivers();
    //return a.exec();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test1");
    db.setUserName("root");
    db.setPassword("1111");
    bool ok = db.open();
    QSqlQuery query;
    query.exec("INSERT INTO build (id_build, name_build)"
                  "VALUES (0, 'lolkek')");
    qDebug() << ok;



/***************************************************************
 *                            Table
 **************************************************************/
/*
   QSqlTableModel model;
   model.setTable("build");
   ui->tableView->setModel(&model);
   ui->tableView->show();
*/
    QSqlTableModel *model;
    model = new QSqlTableModel(this);
    model->setTable("build");
    model->select();

    ui->tableView->setModel(model);
    ui->floor_2->addItem("1");
    ui->floor_2->addItem("4");
    ui->floor_6->addItem("1");
    ui->floor_6->addItem("4");
    ui->BuildPool->addItem("1");
    ui->BuildPool->addItem("2");
    on_init_button_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tab1()
{
    //extra options:
    int ext_doors = 0;
    if(ui->Conferencehall->isChecked()){
        ext_doors += 1;
    }
    if(ui->restaurant->isChecked()){
        ext_doors += 2;
    }
    if(ui->floor2->isChecked()){
        ext_doors += 4;
    }
    if(ui->default3->isChecked()){
        ext_doors += 8;
    }
    if(ui->default4->isChecked()){
        ext_doors += 16;
    }
    if(ui->cafe->isChecked()){
        ext_doors += 32;
    }
    if(ui->gym->isChecked()){
        ext_doors += 64;
    }
    if(ui->safe->isChecked()){
        ext_doors += 128;
    }

    //lux options:
    int lux_options = 0;
    if(ui->lux_a->isChecked()){
        lux_options = 3;
    }
    else if(ui->lux_b->isChecked()){
        lux_options = 5;
    }
    else if(ui->lux_c->isChecked()){
        lux_options = 9;
    }
    else if(ui->lux_d->isChecked()){
        lux_options = 11;
    }


    QString date_str = ui->dateTimeEdit->date().toString("dd.MM.yyyy");
    QString time_str = ui->dateTimeEdit->time().toString("mm:HH");
    int floor = ui->floor_2->currentText().toInt();//itemData(ui->floor_2->currentIndex()).toInt();
   boolean state = card.guest_write(card.hotel_code_test, ui->num_of_room_edit->text().toInt(), floor,QDate::fromString(date_str, "dd.MM.yyyy"), QTime::fromString(time_str, "mm:HH") ,lux_options,ext_doors);
   if(state == 0)
       ui->CardState->setText("Успешно");
   else
       ui->CardState->setText("Ошибка записи");
}

void MainWindow::tab2()
{

    //lux options:
    int lux_options = 0;
    if(ui->lux_door_set->isChecked()){
       lux_options = 0xD;
    }
    if(ui->lux_a_set->isChecked()){
        lux_options = 0xE;
    }
    else if(ui->lux_b_set->isChecked()){
        lux_options = 0xF;
    }
    else if(ui->lux_c_set->isChecked()){
        lux_options = 0x10;
    }
    else if(ui->lux_d_set->isChecked()){
        lux_options = 0x11;
    }

int floor = ui->floor_6->currentText().toInt();
   boolean state = card.guest_set_write(card.hotel_code_test, ui->num_of_room_edit_2->text().toInt(), floor, lux_options);
   if(state == 0)
       ui->CardState->setText("Успешно");
   else
       ui->CardState->setText("Ошибка записи");
}

void MainWindow::on_WriteButton_clicked()
{
    card.read_to_log();
    on_init_button_clicked();
    switch(ui->tabWidget->currentIndex()){
        case 0: tab1();
        break;
        case 1: tab2();
    }

}


void MainWindow::on_init_button_clicked()
{
    QString init_complete = "Готов к работе";
    QString init_error = "Ошибка инициализации";
    if(card.auth() == 1){
        ui->init_button->setText(init_error);
    }
    else{
        ui-> init_button->setText(init_complete);
    }
}



void MainWindow::on_night_edit_textChanged(const QString &arg1)
{
    QDate date_now = QDate::currentDate();
    QDate add_date_now = date_now.addDays(ui->night_edit->text().toInt());
    ui->dateTimeEdit->setDate(add_date_now);
}
