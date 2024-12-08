#include "stafftablewidget.h"
#include "ui_stafftablewidget.h"

staffTableWidget::staffTableWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::staffTableWidget)
{
    ui->setupUi(this);
}

staffTableWidget::~staffTableWidget()
{
    delete ui;
}
