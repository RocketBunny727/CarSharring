#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QSoundEffect> // Подключаем QSoundEffect

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
    void playMenuSound(); // Метод для воспроизведения звука
    void playExitSound();

    void on_auto_list_button_clicked();
    void on_exit_button_clicked();
    void on_user_list_button_clicked();
    void on_partner_list_button_clicked();
    void on_staff_list_button_clicked();
    void on_setting_button_clicked();

    void stopSlideShowAndResizeButtons();

private:
    Ui::MainWindow *ui;
    QGraphicsOpacityEffect *opacityEffect; // Для эффекта затухания
    QTimer *timer; // Таймер для смены картинок
    QSoundEffect *menuSoundEffect; // Объект для воспроизведения звука
    QSoundEffect *exitSoundEffect; // Объект для воспроизведения звука выхода
};

#endif // MAINWINDOW_H
