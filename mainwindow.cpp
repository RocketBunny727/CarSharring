#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSoundEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/assets/icon.png"));

    menuSoundEffect = new QSoundEffect(this);
    exitSoundEffect = new QSoundEffect(this);
    menuSoundEffect->setSource(QUrl("qrc:/sounds/assets/sounds/SelectingMenuSound.wav"));
    exitSoundEffect->setSource(QUrl("qrc:/sounds/assets/sounds/ExitMenuSound.wav"));

    menuSoundEffect->setVolume(1.0);

    opacityEffect = new QGraphicsOpacityEffect(this);
    ui->label_pic->setGraphicsEffect(opacityEffect);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::changeImage);
    timer->start(5000);

    changeImage();
}

MainWindow::~MainWindow()
{
    delete menuSoundEffect;
    delete ui;
}

void MainWindow::changeImage()
{
    QStringList imagePaths = {
        ":/images/assets/wall_pics/1.jpg", ":/images/assets/wall_pics/2.jpg", ":/images/assets/wall_pics/3.jpg",
        ":/images/assets/wall_pics/4.jpg", ":/images/assets/wall_pics/5.jpg", ":/images/assets/wall_pics/6.jpg",
        ":/images/assets/wall_pics/7.jpg", ":/images/assets/wall_pics/8.jpg", ":/images/assets/wall_pics/9.jpg",
        ":/images/assets/wall_pics/10.jpg", ":/images/assets/wall_pics/11.jpg", ":/images/assets/wall_pics/12.jpg",
        ":/images/assets/wall_pics/13.jpg", ":/images/assets/wall_pics/14.jpg", ":/images/assets/wall_pics/15.jpg",
        ":/images/assets/wall_pics/16.jpg", ":/images/assets/wall_pics/17.jpg", ":/images/assets/wall_pics/18.jpg",
        ":/images/assets/wall_pics/19.jpg", ":/images/assets/wall_pics/20.jpg", ":/images/assets/wall_pics/21.jpg",
        ":/images/assets/wall_pics/22.jpg", ":/images/assets/wall_pics/23.jpg", ":/images/assets/wall_pics/24.jpg"
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

void MainWindow::playMenuSound()
{
    menuSoundEffect->play();
}

void MainWindow::playExitSound()
{
    exitSoundEffect->play();
}

void MainWindow::on_auto_list_button_clicked()
{
    playMenuSound();
}

void MainWindow::on_user_list_button_clicked()
{
    playMenuSound();
}

void MainWindow::on_partner_list_button_clicked()
{
    playMenuSound();
}

void MainWindow::on_staff_list_button_clicked()
{
    playMenuSound();
}

void MainWindow::on_setting_button_clicked()
{
    playMenuSound();
}

void MainWindow::on_exit_button_clicked()
{
    playExitSound();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход из приложения", "Выйти из приложения?",
                                  QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Ok)
    {
        QApplication::quit();
    }
    if (reply == QMessageBox::Cancel)
    {
        playMenuSound();
    }
}
