#ifndef USERTABLEWIDGET_H
#define USERTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class userTableWidget;
}

class userTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit userTableWidget(QWidget *parent = nullptr);
    ~userTableWidget();

private:
    Ui::userTableWidget *ui;
};

#endif // USERTABLEWIDGET_H
