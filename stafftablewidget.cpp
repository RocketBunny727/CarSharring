#include "stafftablewidget.h"
#include "ui_stafftablewidget.h"

staffTableWidget::staffTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::staffTableWidget)
{
    ui->setupUi(this);
}

staffTableWidget::~staffTableWidget()
{
    delete ui;
}
