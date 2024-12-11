#include "stafftableinsertwindow.h"
#include "ui_stafftableinsertwindow.h"

StaffTableInsertWindow::StaffTableInsertWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StaffTableInsertWindow)
{
    ui->setupUi(this);
    setupDatabase();
}

StaffTableInsertWindow::~StaffTableInsertWindow()
{
    delete ui;
}

void StaffTableInsertWindow::setupDatabase()
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

void StaffTableInsertWindow::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void StaffTableInsertWindow::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void StaffTableInsertWindow::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void StaffTableInsertWindow::updateTextColor()
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

void StaffTableInsertWindow::updateLabel(const QColor &color) {

}

void StaffTableInsertWindow::on_closeButton_clicked()
{
    this->close();
    emit playExitSound();
}

void StaffTableInsertWindow::on_insertButton_clicked()
{
    insertData();
    emit playMenuSound();
}

void StaffTableInsertWindow::insertData()
{
    QString name = ui->nameLineEdit->text();
    QString birthday = ui->yearLineEdit->text();
    QString post = ui->postLineEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString email = ui->emailLineEdit->text();

    if (name.isEmpty() || birthday.isEmpty() || post.isEmpty() || phone.isEmpty() || email.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    QSqlQuery query;

    if (!idForUpdate.isEmpty()) {
        query.prepare("UPDATE staffTable SET name = :name, birthday = :birthday, post = :post, phone = :phone, email = :email WHERE id = :id");
        query.bindValue(":id", idForUpdate);
    } else {
        query.prepare("INSERT INTO staffTable (name, birthday, post, phone, email) VALUES (:name, :birthday, :post, :phone, :email)");
    }

    query.bindValue(":name", name);
    query.bindValue(":birthday", birthday);
    query.bindValue(":post", post);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Ошибка вставки/обновления данных:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка вставки/обновления данных: " + query.lastError().text());
    } else {
        qDebug() << "Данные успешно вставлены/обновлены!";
        QMessageBox::information(this, "Успех", "Данные сотрудника успешно добавлены/обновлены!");
        emit dataInserted();
        close();
    }
}


void StaffTableInsertWindow::setDataForEditing(const QString &id, const QString &name, const QString &birthday,
                                              const QString &post, const QString &phone, const QString &email)
{
    ui->nameLineEdit->setText(name);
    ui->yearLineEdit->setText(birthday);
    ui->postLineEdit->setText(post);
    ui->phoneLineEdit->setText(phone);
    ui->emailLineEdit->setText(email);

    this->idForUpdate = id;
}
