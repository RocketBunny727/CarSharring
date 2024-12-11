#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QColor>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QSoundEffect>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFont>
#include "optionswidget.h"
#include "slide.h"
#include "autotablewidget.h"
#include "autotableinsertwindow.h"
#include "usertablewidget.h"
#include "partnertablewidget.h"
#include "stafftablewidget.h"

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
    void onOptionsClose();
    void changeBackgroundColor(const QColor &color);
    void changeButtonColor(const QColor &color);
    void fontColorChanged(const QColor &color);
    void changeButtonFont(int size);
    void resetSettings();
    void restoreButtonSizes();
    void updateTextColor();
    void changeButtonHeight(int height);
    void showAutoTableWidget();
    void showUserTableWidget();
    void showPartnerTableWidget();
    void showStaffTableWidget();
    void saveSettings();
    void loadSettings();

private:
    Ui::MainWindow *ui;
    QGraphicsOpacityEffect *opacityEffect;
    QTimer *timer;
    QSoundEffect *menuSoundEffect;
    QSoundEffect *exitSoundEffect;
    OptionsWidget *optionsWidget;
    Slide *slideWidget;
    AutoTableWidget *autoTableWidget;
    AutoTableInsertWindow *autoTableInsertWindow;
    UserTableWidget *userTableWidget;
    PartnerTableWidget *partnerTableWidget;
    StaffTableWidget *staffTableWidget;
};

#endif // MAINWINDOW_H
