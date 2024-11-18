#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/assets/icon.png"));

    opacityEffect = new QGraphicsOpacityEffect(this);
    ui->label_pic->setGraphicsEffect(opacityEffect);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::changeImage);
    timer->start(5000);

    changeImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeImage()
{
    QStringList imagePaths = {
        ":/images/assets/wall_pics/1.jpg", ":/images/assets/wall_pics/2.jpg", ":/images/assets/wall_pics/3.jpg",
        ":/images/assets/wall_pics/4.jpg", ":/images/assets/wall_pics/5.jpg", ":/images/assets/wall_pics/6.jpg",
        ":/images/assets/wall_pics/7.jpg", ":/images/assets/wall_pics/8.jpg", ":/images/assets/wall_pics/9.jpg",
        ":/images/assets/wall_pics/10.jpg", ":/images/assets/wall_pics/11.jpg", ":/images/assets/wall_pics/12.jpg"
    };

    static int currentIndex = 0;
    QString newImage = imagePaths[currentIndex];
    currentIndex = (currentIndex + 1) % imagePaths.size();

    QPropertyAnimation *fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
    fadeOut->setDuration(1000);
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);
    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);

    connect(fadeOut, &QPropertyAnimation::finished, this, [this, newImage] {
        ui->label_pic->setPixmap(QPixmap(newImage).scaled(ui->label_pic->size(), Qt::KeepAspectRatio));

        QPropertyAnimation *fadeIn = new QPropertyAnimation(opacityEffect, "opacity");
        fadeIn->setDuration(1000);
        fadeIn->setStartValue(0);
        fadeIn->setEndValue(1);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    });
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
