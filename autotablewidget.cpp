#include "autotablewidget.h"
#include "ui_autotablewidget.h"

autoTableWidget::autoTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::autoTableWidget)
{
    ui->setupUi(this);
}

autoTableWidget::~autoTableWidget()
{
    delete ui;
}
