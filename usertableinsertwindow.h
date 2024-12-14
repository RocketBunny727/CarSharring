#ifndef USERTABLEINSERTWINDOW_H
#define USERTABLEINSERTWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QRegularExpression>

namespace Ui {
class UserTableInsertWindow;
}

class UserTableInsertWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserTableInsertWindow(QWidget *parent = nullptr);
    ~UserTableInsertWindow();
    void setDataForEditing(const QString &id, const QString &name, const QString &birthday, const QString &status,
                           const QString &phone, const QString &email);

signals:
    void playMenuSound();
    void playExitSound();
    void dataInserted();

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
    Ui::UserTableInsertWindow *ui;
    QSqlDatabase db;
    void setupDatabase();
    void insertData();
    QString idForUpdate;
};

#endif // USERTABLEINSERTWINDOW_H
