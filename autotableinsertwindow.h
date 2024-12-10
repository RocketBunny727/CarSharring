#ifndef AUTOTABLEINSERTWINDOW_H
#define AUTOTABLEINSERTWINDOW_H

#include <QMainWindow>

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
    void setupDatabase();
    void on_insertButton_clicked();

public slots:
    void updateButtonColor(const QColor &color);
    void updateButtonFontColor(const QColor &color);
    void updateButtonHeight(int height);
    void updateLabel(const QColor &color);

private:
    Ui::AutoTableInsertWindow *ui;
};

#endif // AUTOTABLEINSERTWINDOW_H
