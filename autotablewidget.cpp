#include "autotablewidget.h"
#include "ui_autotablewidget.h"

autoTableWidget::autoTableWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::autoTableWidget)
{
    ui->setupUi(this);
}

autoTableWidget::~autoTableWidget()
{
    delete ui;
}
