#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsOpacityEffect>
#include <QTimer>

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

    void on_auto_list_button_clicked();
    void on_exit_button_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsOpacityEffect *opacityEffect;  // Для эффекта затухания
    QTimer *timer;  // Для таймера, который меняет картинку
};

#endif // MAINWINDOW_H
