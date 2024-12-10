#ifndef AUTOTABLEINSERTWINDOW_H
#define AUTOTABLEINSERTWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
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

signals:
    void playMenuSound();
    void playExitSound();

private slots:
    void on_closeButton_clicked();
    void updateTextColor();
    void on_insertButton_clicked();

public slots:
    void updateButtonColor(const QColor &color);
    void updateButtonFontColor(const QColor &color);
    void updateButtonHeight(int height);
    void updateLabel(const QColor &color);

private:
    Ui::AutoTableInsertWindow *ui;
    QSqlDatabase db;
    void setupDatabase();
};

#endif // AUTOTABLEINSERTWINDOW_H
