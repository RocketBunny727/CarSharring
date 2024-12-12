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
    void fontColorChanged(const QColor &color);
    void fontSizeChanged(int size);
    void buttonSizeChanged(int size);
    void buttonHeightChanged(int height);
    void buttonFontChanged(int size);
    void resetSettings();
    void closeOptions();
    void playMenuSound();
    void playExitSound();
    void screenModeChanged();

private slots:
    void on_backgroundColorButton_clicked();
    void on_buttonColorButton_clicked();
    void on_fontColorButton_clicked();
    void on_resetButton_clicked();
    void on_closeButton_clicked();
    void updateTextColor();
    void on_fontSizeSlider_valueChanged(int value);
    void on_spinBox_valueChanged(int arg1);

    void on_screenButton_clicked();

public slots:
    void updateButtonColor(const QColor &color);
    void updateButtonFontColor(const QColor &color);
    void updateButtonHeight(int height);
    void updateLabel(const QColor &color);

private:
    Ui::OptionsWidget *ui;
};

#endif // OPTIONSWIDGET_H
