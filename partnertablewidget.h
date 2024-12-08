#ifndef PARTNERTABLEWIDGET_H
#define PARTNERTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class partnerTableWidget;
}

class partnerTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit partnerTableWidget(QWidget *parent = nullptr);
    ~partnerTableWidget();

private:
    Ui::partnerTableWidget *ui;
};

#endif // PARTNERTABLEWIDGET_H
