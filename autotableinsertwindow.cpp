#include "autotableinsertwindow.h"
#include "ui_autotableinsertwindow.h"

AutoTableInsertWindow::AutoTableInsertWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AutoTableInsertWindow)
{
    ui->setupUi(this);
}

AutoTableInsertWindow::~AutoTableInsertWindow()
{
    delete ui;
}

void AutoTableInsertWindow::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void AutoTableInsertWindow::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void AutoTableInsertWindow::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void AutoTableInsertWindow::updateTextColor()
{
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        QColor buttonColor = buttonPalette.color(QPalette::Button);
        QColor buttonTextColor;

        if (buttonColor.lightness() > 128) {
            buttonTextColor = Qt::black;
        }
        else {
            buttonTextColor = Qt::white;
        }

        buttonPalette.setColor(QPalette::ButtonText, buttonTextColor);
        button->setPalette(buttonPalette);
    }
}

void AutoTableInsertWindow::updateLabel(const QColor &color) {

}

void AutoTableInsertWindow::on_closeButton_clicked()
{
    this->close();
    emit playExitSound();
}


void AutoTableInsertWindow::on_insertButton_clicked()
{
    emit playMenuSound();
}

