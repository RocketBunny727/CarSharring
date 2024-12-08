#include "partnertablewidget.h"
#include "ui_partnertablewidget.h"

partnerTableWidget::partnerTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::partnerTableWidget)
{
    ui->setupUi(this);
}

partnerTableWidget::~partnerTableWidget()
{
    delete ui;
}
