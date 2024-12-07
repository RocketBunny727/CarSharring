#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QSoundEffect>
#include "optionswidget.h"
#include "slide.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changeImage();
    void playMenuSound();
    void playExitSound();
    void on_auto_list_button_clicked();
    void on_exit_button_clicked();
    void on_user_list_button_clicked();
    void on_partner_list_button_clicked();
    void on_staff_list_button_clicked();
    void on_setting_button_clicked();
    void stopSlideShowAndResizeButtons();
    void showOptionsWidget();
    void showSliderWidget();

private:
    Ui::MainWindow *ui;
    QGraphicsOpacityEffect *opacityEffect;
    QTimer *timer;
    QSoundEffect *menuSoundEffect;
    QSoundEffect *exitSoundEffect;
    OptionsWidget *optionsWidget;
    Slide *slideWidget;
};

#endif // MAINWINDOW_H
