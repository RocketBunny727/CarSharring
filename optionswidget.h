#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include <QColorDialog>

namespace Ui {
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = nullptr);
    ~OptionsWidget();

signals:
    void backgroundColorChanged(const QColor &color);
    void buttonColorChanged(const QColor &color);
    void fontSizeChanged(int size);
    void resetSettings();
    void closeOptions();  // Новый сигнал для закрытия опций

private slots:
    void on_backgroundColorButton_clicked();
    void on_buttonColorButton_clicked();
    void on_fontSizeSpinBox_valueChanged(int value);
    void on_resetButton_clicked();
    void on_closeButton_clicked();  // Новый слот для кнопки закрытия

private:
    Ui::OptionsWidget *ui;
};

#endif // OPTIONSWIDGET_H
