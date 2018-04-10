#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "writecard.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    writecard card;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //work with 1 tab
    void tab1();
    //work with 2 tab
    void tab2();
    //when "write" button pressed forming data and write to the card
    void on_WriteButton_clicked();
    //when "init" button pressed it calls auth() and write result on "CardState" label
    void on_init_button_clicked();
    //make dependency, when night > 0  then add days to date_out
    void on_night_edit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

