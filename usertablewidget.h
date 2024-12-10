#ifndef USERTABLEWIDGET_H
#define USERTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class UserTableWidget;
}

class UserTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserTableWidget(QWidget *parent = nullptr);
    ~UserTableWidget();

private:
    Ui::UserTableWidget *ui;
};

#endif // USERTABLEWIDGET_H
