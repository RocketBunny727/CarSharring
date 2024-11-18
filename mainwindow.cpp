#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/assets/icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_auto_list_button_clicked()
{

}


void MainWindow::on_exit_button_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход из приложения", "Выйти из приложения?",
                                  QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Ok) {
        QApplication::quit();
    }
}

