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
    void playMenuSound(); // Добавляем метод для воспроизведения звука
    void playExitSound();

    void on_auto_list_button_clicked();
    void on_exit_button_clicked();
    void on_user_list_button_clicked();
    void on_partner_list_button_clicked();
    void on_staff_list_button_clicked();
    void on_setting_button_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsOpacityEffect *opacityEffect; // Для эффекта затухания
    QTimer *timer; // Для таймера, который меняет картинку
    QSoundEffect *menuSoundEffect; // Объект для воспроизведения звука
    QSoundEffect *exitSoundEffect;
};

#endif // MAINWINDOW_H
