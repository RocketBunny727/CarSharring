#ifndef AUTOTABLEWIDGET_H
#define AUTOTABLEWIDGET_H

#include <QMainWindow>

namespace Ui {
class autoTableWidget;
}

class autoTableWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit autoTableWidget(QWidget *parent = nullptr);
    ~autoTableWidget();

private:
    Ui::autoTableWidget *ui;
};

#endif // AUTOTABLEWIDGET_H
