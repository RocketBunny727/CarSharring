#include "usertablewidget.h"
#include "ui_usertablewidget.h"

userTableWidget::userTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userTableWidget)
{
    ui->setupUi(this);
}

userTableWidget::~userTableWidget()
{
    delete ui;
}
