#ifndef STAFFTABLEWIDGET_H
#define STAFFTABLEWIDGET_H

#include <QMainWindow>

namespace Ui {
class staffTableWidget;
}

class staffTableWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit staffTableWidget(QWidget *parent = nullptr);
    ~staffTableWidget();

private:
    Ui::staffTableWidget *ui;
};

#endif // STAFFTABLEWIDGET_H
