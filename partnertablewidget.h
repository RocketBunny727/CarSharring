#ifndef PARTNERTABLEWIDGET_H
#define PARTNERTABLEWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableWidgetItem>

namespace Ui {
class PartnerTableWidget;
}

class PartnerTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PartnerTableWidget(QWidget *parent = nullptr);
    ~PartnerTableWidget();

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
    Ui::PartnerTableWidget *ui;
    QSqlDatabase db;
    void setupDatabase();
};

#endif // PARTNERTABLEWIDGET_H
