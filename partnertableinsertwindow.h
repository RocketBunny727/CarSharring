#ifndef PARTNERTABLEINSERTWINDOW_H
#define PARTNERTABLEINSERTWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>

namespace Ui {
class PartnerTableInsertWindow;
}

class PartnerTableInsertWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PartnerTableInsertWindow(QWidget *parent = nullptr);
    ~PartnerTableInsertWindow();
    void setDataForEditing(const QString &id, const QString &name, const QString &role, const QString &contactPerson,
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
    Ui::PartnerTableInsertWindow *ui;
    QSqlDatabase db;
    void setupDatabase();
    void insertData();
    QString idForUpdate;
};

#endif // PARTNERTABLEINSERTWINDOW_H
