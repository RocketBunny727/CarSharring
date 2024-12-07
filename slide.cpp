#include "slide.h"
#include "ui_slide.h"

Slide::Slide(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Slide)
{
    ui->setupUi(this);
}

Slide::~Slide()
{
    delete ui;
}
