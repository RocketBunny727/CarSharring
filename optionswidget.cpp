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



