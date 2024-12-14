#include "rentwindow.h"
#include "ui_rentwindow.h"

RentWindow::RentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RentWindow),
    costPerHour(0),
    costPerDay(0)
{
    ui->setupUi(this);
    connect(ui->durationSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRentCost()));
    connect(ui->unitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateRentCost()));
}

RentWindow::~RentWindow()
{
    delete ui;
}

void RentWindow::setAutoName(QString autoName) {
    ui->label->setText("Выбранное авто: " + autoName);
}

void RentWindow::setCostPerHour(double cost) {
    costPerHour = cost;
}

void RentWindow::setCostPerDay(double cost) {
    costPerDay = cost;
}

void RentWindow::updateRentCost()
{
    emit playExitSound();
    int hours = ui->durationSpinBox->value();
    int timeUnitIndex = ui->unitComboBox->currentIndex();

    double cost = 0;

    if (timeUnitIndex == 0) {
        cost = hours * costPerHour;
    } else if (timeUnitIndex == 1) {
        cost = hours * costPerDay;
    }

    ui->totalTextEdit->setText(QString::number(cost, 'f', 2));
}

void RentWindow::on_calculateButton_clicked()
{
    int hours = ui->durationSpinBox->value();
    int timeUnitIndex = ui->unitComboBox->currentIndex();

    double cost = 0;

    if (timeUnitIndex == 0) {
        cost = hours * costPerHour;
    } else if (timeUnitIndex == 1) {
        cost = hours * costPerDay;
    }

    ui->totalTextEdit->setText(QString::number(cost, 'f', 2));

    emit updateAutoStatus(autoId, "В АРЕНДЕ");

    QMessageBox::information(this, "Рассчитано", "Стоимость аренды: " + QString::number(cost, 'f', 2));
    this->close();
}

void RentWindow::on_closeButton_clicked()
{
    this->close();
}

