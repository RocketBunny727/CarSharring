#ifndef STAFFTABLEWIDGET_H
#define STAFFTABLEWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableWidgetItem>

namespace Ui {
class StaffTableWidget;
}

class StaffTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StaffTableWidget(QWidget *parent = nullptr);
    ~StaffTableWidget();

signals:
    void closeOptions();
    void playMenuSound();
    void playExitSound();

private slots:
    void on_insertButton_clicked();
    void on_closeButton_clicked();
    void on_deleteButton_clicked();
    void on_editButton_clicked();
    void loadTableData();
    void updateTextColor();
    void onDataInserted();

public slots:
    void updateButtonColor(const QColor &color);
    void updateButtonFontColor(const QColor &color);
    void updateButtonHeight(int height);
    void updateLabel(const QColor &color);

private:
    Ui::StaffTableWidget *ui;
    QSqlDatabase db;
    void setupDatabase();
};

#endif // STAFFTABLEWIDGET_H
