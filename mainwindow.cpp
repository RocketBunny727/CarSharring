#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , optionsWidget(new OptionsWidget(this))
    , slideWidget(new Slide(this))
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/assets/icon.png"));

    // Добавление виджетов в stackedWidget
    ui->workZoneWidget->addWidget(slideWidget);
    ui->workZoneWidget->addWidget(optionsWidget);
    ui->workZoneWidget->setCurrentWidget(slideWidget);  // По умолчанию показываем slideWidget

    // Настройка звуков
    menuSoundEffect = new QSoundEffect(this);
    exitSoundEffect = new QSoundEffect(this);
    menuSoundEffect->setSource(QUrl("qrc:/sounds/assets/sounds/SelectingMenuSound.wav"));
    exitSoundEffect->setSource(QUrl("qrc:/sounds/assets/sounds/ExitMenuSound.wav"));
    menuSoundEffect->setVolume(1.0);

    // Настройка смены изображений
    opacityEffect = new QGraphicsOpacityEffect(this);
    slideWidget->findChild<QLabel*>("label_pic")->setGraphicsEffect(opacityEffect);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::changeImage);
    timer->start(5000);

    changeImage();

    // Подключение сигналов для optionsWidget
    connect(optionsWidget, &OptionsWidget::backgroundColorChanged, this, &MainWindow::changeBackgroundColor);
    connect(optionsWidget, &OptionsWidget::buttonColorChanged, this, &MainWindow::changeButtonColor);
    connect(optionsWidget, &OptionsWidget::fontSizeChanged, this, &MainWindow::changeButtonFont);
    connect(optionsWidget, &OptionsWidget::buttonSizeChanged, this, &MainWindow::changeButtonSize);
    connect(optionsWidget, &OptionsWidget::resetSettings, this, &MainWindow::resetSettings);
    connect(optionsWidget, &OptionsWidget::closeOptions, this, &MainWindow::onOptionsClose);
    connect(optionsWidget, &OptionsWidget::playMenuSound, this, &MainWindow::playMenuSound);
    connect(optionsWidget, &OptionsWidget::playExitSound, this, &MainWindow::playExitSound);
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
        slideWidget->findChild<QLabel*>("label_pic")->setPixmap(QPixmap(newImage).scaled(slideWidget->findChild<QLabel*>("label_pic")->size(), Qt::KeepAspectRatio));

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
    stopSlideShowAndResizeButtons();
    playMenuSound();
}

void MainWindow::on_user_list_button_clicked()
{
    stopSlideShowAndResizeButtons();
    playMenuSound();
}

void MainWindow::on_partner_list_button_clicked()
{
    stopSlideShowAndResizeButtons();
    playMenuSound();
}

void MainWindow::on_staff_list_button_clicked()
{
    stopSlideShowAndResizeButtons();
    playMenuSound();
}

void MainWindow::on_setting_button_clicked()
{
    stopSlideShowAndResizeButtons();
    showOptionsWidget();
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

void MainWindow::stopSlideShowAndResizeButtons()
{
    timer->stop();
    slideWidget->findChild<QLabel*>("label_pic")->clear();

    QList<QPushButton *> buttons = {ui->auto_list_button, ui->user_list_button, ui->partner_list_button, ui->staff_list_button, ui->setting_button, ui->exit_button};

    for (QPushButton *button : buttons) {
        if (button->minimumWidth() != 300) {
            QPropertyAnimation *animation = new QPropertyAnimation(button, "minimumWidth");
            animation->setDuration(500);
            animation->setStartValue(button->minimumWidth());
            animation->setEndValue(300);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
}

void MainWindow::showOptionsWidget()
{
    ui->workZoneWidget->setCurrentWidget(optionsWidget);
    slideWidget->findChild<QLabel*>("label_pic")->setGraphicsEffect(opacityEffect);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::changeImage);
    timer->start(5000);

    changeImage();
}

void MainWindow::showSliderWidget()
{
    ui->workZoneWidget->setCurrentWidget(slideWidget);
}

void MainWindow::onOptionsClose() {
    showSliderWidget();
    restoreButtonSizes();
}

void MainWindow::changeBackgroundColor(const QColor &color) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, color);
    this->setPalette(palette);
    updateTextColor();
}

void MainWindow::changeButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->auto_list_button, ui->user_list_button, ui->partner_list_button, ui->staff_list_button, ui->setting_button, ui->exit_button};

    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void MainWindow::changeButtonSize(int size) {
    QList<QPushButton *> buttons = {ui->auto_list_button, ui->user_list_button, ui->partner_list_button, ui->staff_list_button, ui->setting_button, ui->exit_button};
    for (QPushButton *button : buttons) {
        button->setMinimumSize(size, button->height());
    }
}

void MainWindow::changeButtonFont(int size) {
    QFont font = QApplication::font();
    font.setPointSize(size);
    QApplication::setFont(font);

    QList<QPushButton *> buttons = {ui->auto_list_button, ui->user_list_button, ui->partner_list_button, ui->staff_list_button, ui->setting_button, ui->exit_button};
    for (QPushButton *button : buttons) {
        button->setFont(font);
    }
}

void MainWindow::resetSettings() {
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#1e1e1e"));
    this->setPalette(palette);

    QList<QPushButton *> buttons = {ui->auto_list_button, ui->user_list_button, ui->partner_list_button, ui->staff_list_button, ui->setting_button, ui->exit_button};

    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::Button, QColor("#545454"));
        button->setPalette(buttonPalette);
    }

    QFont font = this->font();
    font.setPointSize(12);
    this->setFont(font);
}

void MainWindow::restoreButtonSizes() {
    QList<QPushButton *> buttons = {ui->auto_list_button, ui->user_list_button, ui->partner_list_button, ui->staff_list_button, ui->setting_button, ui->exit_button};
    for (QPushButton *button : buttons) {
        if (button->minimumWidth() != 701) {
            QPropertyAnimation *animation = new QPropertyAnimation(button, "minimumWidth");
            animation->setDuration(500);
            animation->setStartValue(button->minimumWidth());
            animation->setEndValue(701);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
}

void MainWindow::updateTextColor()
{
    QPalette windowPalette = this->palette();
    QColor backgroundColor = windowPalette.color(QPalette::Window);
    QColor buttonColor = windowPalette.color(QPalette::Button);

    QList<QPushButton *> buttons = {ui->auto_list_button, ui->user_list_button, ui->partner_list_button, ui->staff_list_button, ui->setting_button, ui->exit_button};

    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        QColor textColor = Qt::black;

        if (backgroundColor.lightness() < 128 || buttonColor.lightness() < 128) {
            textColor = Qt::white;
        }

        buttonPalette.setColor(QPalette::ButtonText, textColor);
        button->setPalette(buttonPalette);
    }
}
