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
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        emit backgroundColorChanged(color);
    }
}

void OptionsWidget::on_buttonColorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        emit buttonColorChanged(color);
    }
}

void OptionsWidget::on_fontSizeSpinBox_valueChanged(int value)
{
    emit fontSizeChanged(value);
}

void OptionsWidget::on_resetButton_clicked()
{
    emit resetSettings();
}

void OptionsWidget::on_closeButton_clicked()
{
    emit closeOptions();  // Сигнал для закрытия опций
}
