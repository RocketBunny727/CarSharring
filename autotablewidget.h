#ifndef AUTOTABLEWIDGET_H
#define AUTOTABLEWIDGET_H

#include <QWidget>

namespace Ui {
class autoTableWidget;
}

class autoTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit autoTableWidget(QWidget *parent = nullptr);
    ~autoTableWidget();

private:
    Ui::autoTableWidget *ui;
};

#endif // AUTOTABLEWIDGET_H
