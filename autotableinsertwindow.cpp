#include "autotableinsertwindow.h"
#include "ui_autotableinsertwindow.h"

AutoTableInsertWindow::AutoTableInsertWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AutoTableInsertWindow)
{
    ui->setupUi(this);
    setupDatabase();

    // Подключаем сигналы к слотам
    connect(ui->statusComboBox, &QComboBox::currentTextChanged, this, &AutoTableInsertWindow::updateCost);
    connect(ui->yearLineEdit, &QLineEdit::textChanged, this, &AutoTableInsertWindow::updateCost);
    connect(ui->mileageLineEdit, &QLineEdit::textChanged, this, &AutoTableInsertWindow::updateCost);
    connect(ui->transmissionComboBox, &QComboBox::currentTextChanged, this, &AutoTableInsertWindow::updateCost);
    connect(ui->costCheckBox, &QCheckBox::toggled, this, &AutoTableInsertWindow::toggleCostInputs);

    // Изначально скрываем элементы ввода цены
    toggleCostInputs(ui->costCheckBox->isChecked());
}

AutoTableInsertWindow::~AutoTableInsertWindow()
{
    delete ui;
}

void AutoTableInsertWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("471979");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    } else {
        qDebug() << "Подключение успешно!!! (AutoTableInsertWindow)";
    }
}

void AutoTableInsertWindow::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void AutoTableInsertWindow::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void AutoTableInsertWindow::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void AutoTableInsertWindow::updateTextColor()
{
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        QColor buttonColor = buttonPalette.color(QPalette::Button);
        QColor buttonTextColor;

        if (buttonColor.lightness() > 128) {
            buttonTextColor = Qt::black;
        } else {
            buttonTextColor = Qt::white;
        }

        buttonPalette.setColor(QPalette::ButtonText, buttonTextColor);
        button->setPalette(buttonPalette);
    }
}

void AutoTableInsertWindow::updateLabel(const QColor &color) {

}

void AutoTableInsertWindow::on_closeButton_clicked()
{
    this->close();
    emit playExitSound();
}

void AutoTableInsertWindow::on_insertButton_clicked()
{
    insertData();
    emit playMenuSound();
}

void AutoTableInsertWindow::insertData()
{
    QString name = ui->nameLineEdit->text();
    QString yearStr = ui->yearLineEdit->text();
    QString mileageStr = ui->mileageLineEdit->text();
    QString status = ui->statusComboBox->currentText();
    QString transmission = ui->transmissionComboBox->currentText();
    QString wheelSide = ui->wheelComboBox->currentText();
    QString costPerHour = ui->costPerHourLineEdit->text();
    QString costPerDay = ui->costPerDayLineEdit->text();

    if (name.isEmpty() || yearStr.isEmpty() || mileageStr.isEmpty() || status.isEmpty() || transmission.isEmpty() || wheelSide.isEmpty() || costPerHour.isEmpty() || costPerDay.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    int year = yearStr.toInt();
    int mileage = mileageStr.toInt();

    // Проверка года выпуска
    if (year > 2024 || year < 1990) {
        QMessageBox::critical(this, "Ошибка", "Авто слишком старое или введен неправильный год!");
        return;
    }
    if (year < 0) {
        QMessageBox::critical(this, "Ошибка", "Неправильный год!");
        return;
    }

    // Проверка пробега
    if (mileage < 0 || mileage > 500000) {
        QMessageBox::critical(this, "Ошибка", "Слишком большой пробег для авто или неправильный пробег!");
        return;
    }

    // Проверка состояния "Новая"
    if (status == "Новая" && mileage > 50000) {
        status = "Рабочая";
        ui->statusComboBox->setCurrentText(status);
    }

    QSqlQuery query;

    if (!idForUpdate.isEmpty()) {
        query.prepare("UPDATE autoTable SET name = :name, year = :year, mileage = :mileage, transmission = :transmission, "
                      "wheel_side = :wheel_side, status = :status, cost_per_hour = :cost_per_hour, cost_per_day = :cost_per_day "
                      "WHERE id = :id");
        query.bindValue(":id", idForUpdate);
    } else {
        query.prepare("INSERT INTO autoTable (name, year, mileage, transmission, wheel_side, status, cost_per_hour, cost_per_day) "
                      "VALUES (:name, :year, :mileage, :transmission, :wheel_side, :status, :cost_per_hour, :cost_per_day)");
    }

    query.bindValue(":name", name);
    query.bindValue(":year", yearStr);
    query.bindValue(":mileage", mileageStr);
    query.bindValue(":transmission", transmission);
    query.bindValue(":wheel_side", wheelSide);
    query.bindValue(":status", status);
    query.bindValue(":cost_per_hour", costPerHour);
    query.bindValue(":cost_per_day", costPerDay);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка выполнения запроса: " + query.lastError().text());
    } else {
        qDebug() << "Данные успешно добавлены или обновлены!";
        QMessageBox::information(this, "Успех", "Авто успешно добавлено/обновлено!");
        emit dataInserted();
        this->close();
    }
}


void AutoTableInsertWindow::setDataForEditing(const QString &id, const QString &name, const QString &year,
                                              const QString &mileage, const QString &transmission, const QString &wheelSide,
                                              const QString &status, const QString &costPerHour, const QString &costPerDay)
{
    ui->nameLineEdit->setText(name);
    ui->yearLineEdit->setText(year);
    ui->mileageLineEdit->setText(mileage);
    ui->costPerHourLineEdit->setText(costPerHour);
    ui->costPerDayLineEdit->setText(costPerDay);
    ui->statusComboBox->setCurrentText(status);
    ui->transmissionComboBox->setCurrentText(transmission);
    ui->wheelComboBox->setCurrentText(wheelSide);

    this->idForUpdate = id;
}

void AutoTableInsertWindow::updateCost()
{
    if (ui->costCheckBox->isChecked()) {
        return;
    }

    QString status = ui->statusComboBox->currentText();
    int year = ui->yearLineEdit->text().toInt();
    int mileage = ui->mileageLineEdit->text().toInt();
    QString transmission = ui->transmissionComboBox->currentText();

    double costPerHour = 0.0;

    if (status == "Разбита" || status == "Неисправна" || status == "Не подлежит восстановлению") {
        costPerHour = 0.0;
    } else {
        costPerHour = 1500.0;
        if (status == "Требует ремонта") {
            costPerHour /= 2;
        }
        if (year < 2000) {
            costPerHour -= 200.0;
        } else {
            costPerHour += (year - 2000) * 25;
        }
        if (transmission == "АКПП" || transmission == "Вариатор" || transmission == "Робот") {
            costPerHour += 500.0;
        } else if (transmission == "МКПП") {
            costPerHour += 200.0;
        }
        if (mileage < 50000) {
            costPerHour += 500.0;
        } else if (mileage >= 50000 && mileage <= 100000) {
            costPerHour += 250.0;
        } else if (mileage > 100000 && mileage <= 200000) {
            costPerHour += 100.0;
        } else if(mileage > 280000){
            costPerHour -= 250;
        }
    }

    ui->costPerHourLineEdit->setText(QString::number(costPerHour));
    ui->costPerDayLineEdit->setText(QString::number(costPerHour * 20));
}

void AutoTableInsertWindow::toggleCostInputs(bool checked)
{
    ui->costPerHourLabel->setVisible(checked);
    ui->costPerHourLineEdit->setVisible(checked);
    ui->costPerDayLabel->setVisible(checked);
    ui->costPerDayLineEdit->setVisible(checked);

    if (!checked) {
        updateCost();
    }
}
