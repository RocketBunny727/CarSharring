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

void OptionsWidget::on_fontSizeSpinBox_valueChanged(int value)
{
    emit playMenuSound();
    emit fontSizeChanged(value);
}

void OptionsWidget::on_buttonSizeSlider_valueChanged(int value)
{
    emit buttonSizeChanged(value);
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
    QList<QPushButton *> buttons = {ui->backgroundColorButton, ui->buttonColorButton, ui->fontColorButton, ui->closeButton, ui->resetButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void OptionsWidget::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->backgroundColorButton, ui->buttonColorButton, ui->fontColorButton, ui->closeButton, ui->resetButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void OptionsWidget::updateTextColor()
{
    QList<QPushButton *> buttons = {ui->backgroundColorButton, ui->buttonColorButton, ui->fontColorButton, ui->closeButton, ui->resetButton};

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




