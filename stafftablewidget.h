#ifndef STAFFTABLEWIDGET_H
#define STAFFTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class staffTableWidget;
}

class staffTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit staffTableWidget(QWidget *parent = nullptr);
    ~staffTableWidget();

private:
    Ui::staffTableWidget *ui;
};

#endif // STAFFTABLEWIDGET_H
