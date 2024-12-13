#ifndef AUTOTABLEINSERTWINDOW_H
#define AUTOTABLEINSERTWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>

namespace Ui {
class AutoTableInsertWindow;
}

class AutoTableInsertWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AutoTableInsertWindow(QWidget *parent = nullptr);
    ~AutoTableInsertWindow();
    void setDataForEditing(const QString &id, const QString &name, const QString &year, const QString &mileage,
                           const QString &transmission, const QString &wheelSide, const QString &status,
                           const QString &costPerHour, const QString &costPerDay);

signals:
    void playMenuSound();
    void playExitSound();
    void dataInserted();

private slots:
    void on_closeButton_clicked();
    void updateTextColor();
    void on_insertButton_clicked();
    void updateCost();
    void toggleCostInputs(bool checked);

public slots:
    void updateButtonColor(const QColor &color);
    void updateButtonFontColor(const QColor &color);
    void updateButtonHeight(int height);
    void updateLabel(const QColor &color);

private:
    Ui::AutoTableInsertWindow *ui;
    QSqlDatabase db;
    void setupDatabase();
    void insertData();
    QString idForUpdate;
};

#endif // AUTOTABLEINSERTWINDOW_H
