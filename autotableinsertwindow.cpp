#include "autotableinsertwindow.h"
#include "ui_autotableinsertwindow.h"

AutoTableInsertWindow::AutoTableInsertWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AutoTableInsertWindow)
{
    ui->setupUi(this);
    setupDatabase();
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
    QString year = ui->yearLineEdit->text();
    QString mileage = ui->mileageLineEdit->text();
    QString status = ui->statusLineEdit->text();
    QString transmission = ui->transmissionLineEdit->text();
    QString wheelSide = ui->wheelLineEdit->text();
    QString costPerHour = ui->costPerHourLineEdit->text();
    QString costPerDay = ui->costPerDayLineEdit->text();

    if (name.isEmpty() || year.isEmpty() || mileage.isEmpty() || status.isEmpty() || transmission.isEmpty() || wheelSide.isEmpty() || costPerHour.isEmpty() || costPerDay.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
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
    query.bindValue(":year", year);
    query.bindValue(":mileage", mileage);
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
        emit dataInserted(); // Отправляем сигнал об успешной вставке/обновлении данных
        this->close(); // Закрываем окно после успешной вставки
    }
}

void AutoTableInsertWindow::setDataForEditing(const QString &id, const QString &name, const QString &year,
                                              const QString &mileage, const QString &transmission, const QString &wheelSide,
                                              const QString &status, const QString &costPerHour, const QString &costPerDay)
{
    // Заполняем поля формы текущими данными
    ui->nameLineEdit->setText(name);
    ui->yearLineEdit->setText(year);
    ui->mileageLineEdit->setText(mileage);
    ui->statusLineEdit->setText(status);
    ui->transmissionLineEdit->setText(transmission);
    ui->wheelLineEdit->setText(wheelSide);
    ui->costPerHourLineEdit->setText(costPerHour);
    ui->costPerDayLineEdit->setText(costPerDay);

    // Сохраняем ID для последующего обновления записи
    this->idForUpdate = id;
}
