#include "optionswidget.h"
#include "ui_optionswidget.h"

OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWidget)
{
    ui->setupUi(this);
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::on_backgroundColorButton_clicked()
{
    emit playMenuSound();
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        emit backgroundColorChanged(color);
    }
}

void OptionsWidget::on_buttonColorButton_clicked()
{
    emit playMenuSound();
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        emit buttonColorChanged(color);
    }
}

void OptionsWidget::on_fontColorButton_clicked()
{
    emit playMenuSound();
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        emit fontColorChanged(color);
    }
}

void OptionsWidget::on_resetButton_clicked()
{
    emit playMenuSound();
    emit resetSettings();
}

void OptionsWidget::on_closeButton_clicked()
{
    emit playExitSound();
    emit closeOptions();
}

void OptionsWidget::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->backgroundColorButton, ui->buttonColorButton, ui->fontColorButton, ui->screenButton, ui->closeButton, ui->resetButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void OptionsWidget::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->backgroundColorButton, ui->buttonColorButton, ui->fontColorButton, ui->screenButton, ui->closeButton, ui->resetButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void OptionsWidget::updateTextColor()
{
    QList<QPushButton *> buttons = {ui->backgroundColorButton, ui->buttonColorButton, ui->fontColorButton, ui->screenButton, ui->closeButton, ui->resetButton};

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

void OptionsWidget::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->backgroundColorButton, ui->buttonColorButton, ui->fontColorButton, ui->screenButton, ui->closeButton, ui->resetButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void OptionsWidget::on_fontSizeSlider_valueChanged(int value)
{
    value += 41;
    emit buttonHeightChanged(value);
}


void OptionsWidget::on_spinBox_valueChanged(int arg1)
{
    emit playMenuSound();
    emit fontSizeChanged(arg1);
}

void OptionsWidget::updateLabel(const QColor &color) {
    QPalette textPalette = ui->label->palette();
    textPalette.setColor(QPalette::WindowText, color);
    ui->label->setPalette(textPalette);
}


void OptionsWidget::on_screenButton_clicked()
{
    emit screenModeChanged();
}

