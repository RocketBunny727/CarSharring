#include "usertablewidget.h"
#include "ui_usertablewidget.h"

UserTableWidget::UserTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserTableWidget)
{
    ui->setupUi(this);
}

UserTableWidget::~UserTableWidget()
{
    delete ui;
}
