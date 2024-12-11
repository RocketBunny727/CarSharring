#include "partnertableinsertwindow.h"
#include "ui_partnertableinsertwindow.h"

PartnerTableInsertWindow::PartnerTableInsertWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PartnerTableInsertWindow)
{
    ui->setupUi(this);
    setupDatabase();
}

PartnerTableInsertWindow::~PartnerTableInsertWindow()
{
    delete ui;
}

void PartnerTableInsertWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("471979");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    } else {
        qDebug() << "Подключение успешно!!! (PartnerTableInsertWindow)";
    }
}

void PartnerTableInsertWindow::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void PartnerTableInsertWindow::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void PartnerTableInsertWindow::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void PartnerTableInsertWindow::updateTextColor()
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

void PartnerTableInsertWindow::updateLabel(const QColor &color) {

}

void PartnerTableInsertWindow::on_closeButton_clicked()
{
    this->close();
    emit playExitSound();
}

void PartnerTableInsertWindow::on_insertButton_clicked()
{
    insertData();
    emit playMenuSound();
}

void PartnerTableInsertWindow::insertData()
{
    QString name = ui->nameLineEdit->text();
    QString role = ui->roleLineEdit->text();
    QString contactPerson = ui->contactLineEdit->text();
    QString phone = ui->phoneLineEdit->text();
    QString email = ui->emailLineEdit->text();

    if (name.isEmpty() || role.isEmpty() || contactPerson.isEmpty() || phone.isEmpty() || email.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    QSqlQuery query;

    if (!idForUpdate.isEmpty()) {
        query.prepare("UPDATE partnerTable SET name = :name, role = :role, contact_person = :contactPerson, phone = :phone, email = :email WHERE id = :id");
        query.bindValue(":id", idForUpdate);
    } else {
        query.prepare("INSERT INTO partnerTable (name, role, contact_person, phone, email) VALUES (:name, :role, :contactPerson, :phone, :email)");
    }

    query.bindValue(":name", name);
    query.bindValue(":role", role);
    query.bindValue(":contactPerson", contactPerson);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка выполнения запроса: " + query.lastError().text());
    } else {
        qDebug() << "Данные успешно добавлены или обновлены!";
        QMessageBox::information(this, "Успех", "Данные партнера успешно добавлены/обновлены!");
        emit dataInserted();
        this->close();
    }
}

void PartnerTableInsertWindow::setDataForEditing(const QString &id, const QString &name, const QString &role,
                                                 const QString &contactPerson, const QString &phone, const QString &email)
{
    ui->nameLineEdit->setText(name);
    ui->roleLineEdit->setText(role);
    ui->contactLineEdit->setText(contactPerson);
    ui->phoneLineEdit->setText(phone);
    ui->emailLineEdit->setText(email);

    this->idForUpdate = id;
}
