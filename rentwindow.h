#ifndef RENTWINDOW_H
#define RENTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class RentWindow;
}

class RentWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit RentWindow(QWidget *parent = nullptr);
    ~RentWindow();

    void setCostPerHour(double cost);
    void setCostPerDay(double cost);
    void setAutoName(QString autoName);
    QString autoId;

signals:
    void updateAutoStatus(QString id, const QString &status);
    void playMenuSound();
    void playExitSound();

private slots:
    void on_calculateButton_clicked();
    void on_closeButton_clicked();
    void updateRentCost();

private:
    Ui::RentWindow *ui;
    double costPerHour;
    double costPerDay;
};

#endif // RENTWINDOW_H
