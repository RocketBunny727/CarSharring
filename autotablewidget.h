#ifndef AUTOTABLEWIDGET_H
#define AUTOTABLEWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>

namespace Ui {
class AutoTableWidget;
}

class AutoTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutoTableWidget(QWidget *parent = nullptr);
    ~AutoTableWidget();

signals:
    void closeOptions();
    void playMenuSound();
    void playExitSound();

private slots:
    void on_insertButton_clicked();
    void on_closeButton_clicked();
    void on_deleteButton_clicked();
    void loadTableData();
    void updateTextColor();

public slots:
    void updateButtonColor(const QColor &color);
    void updateButtonFontColor(const QColor &color);
    void updateButtonHeight(int height);
    void updateLabel(const QColor &color);

private:
    Ui::AutoTableWidget *ui;
    QSqlDatabase db;
    void setupDatabase();
};

#endif // AUTOTABLEWIDGET_H