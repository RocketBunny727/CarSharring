#include "userTableWidget.h"
#include "usertableinsertwindow.h"
#include "ui_userTableWidget.h"

UserTableWidget::UserTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTableWidget)
{
    ui->setupUi(this);
    setupDatabase();
    loadTableData();
}

UserTableWidget::~UserTableWidget()
{
    delete ui;
}

void UserTableWidget::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("471979");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    } else {
        qDebug() << "Подключение успешно!!! (UserTableWidget)";
    }
}

void UserTableWidget::loadTableData()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id, name, birthday, status, phone, email FROM usersTable", db);

    if (model->lastError().isValid()) {
        qDebug() << "Ошибка в запросе:" << model->lastError().text();
        return;
    }

    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    if (rowCount == 0) {
        qDebug() << "Нет данных для отображения!";
        return;
    }

    ui->userTableWidget->clearContents();
    ui->userTableWidget->setRowCount(rowCount);
    ui->userTableWidget->setColumnCount(columnCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QTableWidgetItem *item = new QTableWidgetItem(data);
            item->setTextAlignment(Qt::AlignCenter);
            ui->userTableWidget->setItem(row, col, item);
        }
    }

    ui->userTableWidget->setColumnWidth(0, 50);
    ui->userTableWidget->horizontalHeader()->resizeSection(0, 50);

    for (int col = 1; col < columnCount; ++col) {
        int maxLength = 0;

        QString headerText = ui->userTableWidget->horizontalHeaderItem(col)->text();
        maxLength = qMax(maxLength, headerText.length());

        for (int row = 0; row < rowCount; ++row) {
            QString cellText = ui->userTableWidget->item(row, col)->text();
            maxLength = qMax(maxLength, cellText.length());
        }

        ui->userTableWidget->setColumnWidth(col, qMax(maxLength * 10, 100));
    }
}


void UserTableWidget::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void UserTableWidget::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void UserTableWidget::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void UserTableWidget::updateTextColor()
{
    QList<QPushButton *> buttons = {ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};

    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        QColor buttonColor = buttonPalette.color(QPalette::Button);
        QColor buttonTextColor;

        if (buttonColor.lightness() > 128) {
            buttonTextColor = Qt::black;
        }
        else {
            buttonTextColor = Qt::white;
        }

        buttonPalette.setColor(QPalette::ButtonText, buttonTextColor);
        button->setPalette(buttonPalette);
    }
}

void UserTableWidget::updateLabel(const QColor &color) {

}

void UserTableWidget::on_insertButton_clicked()
{
    emit playMenuSound();
    UserTableInsertWindow *insertWindow = new UserTableInsertWindow(this);
    connect(insertWindow, &UserTableInsertWindow::dataInserted, this, &UserTableWidget::loadTableData);
    insertWindow->show();
}

void UserTableWidget::on_deleteButton_clicked()
{
    emit playMenuSound();
    int currentRow = ui->userTableWidget->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Ошибка", "Выберите строку для удаления!");
        return;
    }

    QString name = ui->userTableWidget->item(currentRow, 1)->text();

    // Окно подтверждения удаления
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удалить строку?", "Удалить строку: " + name + "?", QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel) {
        emit playExitSound();
        return;
    }

    QTableWidgetItem *idItem = ui->userTableWidget->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::critical(this, "Ошибка", "Не удалось получить ID выбранной строки!");
        return;
    }

    QString id = idItem->text();

    QSqlQuery query;
    query.prepare("DELETE FROM usersTable WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления данных:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка удаления данных: " + query.lastError().text());
    } else {
        qDebug() << "Данные успешно удалены!";
        QMessageBox::information(this, "Успех", "Пользователь успешно удален!");
        loadTableData();
    }
}

void UserTableWidget::on_closeButton_clicked()
{
    emit playExitSound();
    emit closeOptions();
}

void UserTableWidget::on_editButton_clicked()
{
    emit playMenuSound();
    int currentRow = ui->userTableWidget->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Ошибка", "Выберите строку для редактирования!");
        return;
    }

    QString id = ui->userTableWidget->item(currentRow, 0)->text();
    QString name = ui->userTableWidget->item(currentRow, 1)->text();
    QString birthday = ui->userTableWidget->item(currentRow, 2)->text();
    QString status = ui->userTableWidget->item(currentRow, 3)->text();
    QString phone = ui->userTableWidget->item(currentRow, 4)->text();
    QString email = ui->userTableWidget->item(currentRow, 5)->text();

    UserTableInsertWindow *insertWindow = new UserTableInsertWindow(this);
    insertWindow->setWindowTitle("Редактировать пользователя");

    insertWindow->setDataForEditing(id, name, birthday, status, phone, email);

    connect(insertWindow, &UserTableInsertWindow::dataInserted, this, &UserTableWidget::loadTableData);

    insertWindow->show();
}


void UserTableWidget::onDataInserted()
{
    loadTableData();
}
