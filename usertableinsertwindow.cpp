#include "UserTableInsertWindow.h"
#include "ui_UserTableInsertWindow.h"

UserTableInsertWindow::UserTableInsertWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserTableInsertWindow)
{
    ui->setupUi(this);
    setupDatabase();
}

UserTableInsertWindow::~UserTableInsertWindow()
{
    delete ui;
}

void UserTableInsertWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("471979");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    } else {
        qDebug() << "Подключение успешно!!! (UserTableInsertWindow)";
    }
}

void UserTableInsertWindow::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void UserTableInsertWindow::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void UserTableInsertWindow::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void UserTableInsertWindow::updateTextColor()
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

void UserTableInsertWindow::updateLabel(const QColor &color) {

}

void UserTableInsertWindow::on_closeButton_clicked()
{
    this->close();
    emit playExitSound();
}

void UserTableInsertWindow::on_insertButton_clicked()
{
    insertData();
    emit playMenuSound();
}

void UserTableInsertWindow::insertData()
{
    QString name = ui->nameLineEdit->text();
    QString birthday = ui->yearLineEdit->text();
    QString status = ui->statusLineEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString email = ui->emailLineEdit->text();

    if (name.isEmpty() || birthday.isEmpty() || status.isEmpty() || phone.isEmpty() || email.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    QSqlQuery query;

    if (!idForUpdate.isEmpty()) {
        query.prepare("UPDATE usersTable SET name = :name, birthday = :birthday, status = :status, phone = :phone, email = :email WHERE id = :id");
        query.bindValue(":id", idForUpdate);
    } else {
        query.prepare("INSERT INTO usersTable (name, birthday, status, phone, email) VALUES (:name, :birthday, :status, :phone, :email)");
    }

    query.bindValue(":name", name);
    query.bindValue(":birthday", birthday);
    query.bindValue(":status", status);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка выполнения запроса: " + query.lastError().text());
    } else {
        qDebug() << "Данные успешно добавлены или обновлены!";
        QMessageBox::information(this, "Успех", "Данные пользователя успешно добавлены/обновлены!");
        emit dataInserted();
        this->close();
    }
}


void UserTableInsertWindow::setDataForEditing(const QString &id, const QString &name, const QString &birthday,
                                              const QString &status, const QString &phone, const QString &email)
{
    ui->nameLineEdit->setText(name);
    ui->yearLineEdit->setText(birthday);
    ui->statusLineEdit->setText(status);
    ui->phoneLineEdit->setText(phone);
    ui->emailLineEdit->setText(email);

    this->idForUpdate = id;
}
