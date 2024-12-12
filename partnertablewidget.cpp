#include "partnertablewidget.h"
#include "partnertableinsertwindow.h"
#include "ui_partnertablewidget.h"

PartnerTableWidget::PartnerTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartnerTableWidget)
{
    ui->setupUi(this);
    setupDatabase();
    loadTableData();
}

PartnerTableWidget::~PartnerTableWidget()
{
    delete ui;
}

void PartnerTableWidget::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("471979");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    } else {
        qDebug() << "Подключение успешно!!! (PartnerTableWidget)";
    }
}

void PartnerTableWidget::loadTableData()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id, name, role, contact_person, phone, email FROM partnerTable", db);

    if (model->lastError().isValid()) {
        qDebug() << "Ошибка в запросе:" << model->lastError().text();
        return;
    }

    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    if (rowCount == 0) {
        qDebug() << "Таблица пуста или произошла ошибка запроса.";
        return;
    }

    ui->partnertableWidget->clearContents();
    ui->partnertableWidget->setRowCount(rowCount);
    ui->partnertableWidget->setColumnCount(columnCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            QString cellData = model->data(model->index(row, column)).toString();
            QTableWidgetItem *item = new QTableWidgetItem(cellData);
            item->setTextAlignment(Qt::AlignCenter);
            ui->partnertableWidget->setItem(row, column, item);
        }
    }
    ui->partnertableWidget->setColumnWidth(0, 50);
    ui->partnertableWidget->horizontalHeader()->resizeSection(0, 50);


    for (int col = 1; col < columnCount; ++col) {
        int maxLength = 0;
        QString headerText = ui->partnertableWidget->horizontalHeaderItem(col)->text();
        maxLength = qMax(maxLength, headerText.length());

        for (int row = 0; row < rowCount; ++row) {
            QString cellText = ui->partnertableWidget->item(row, col)->text();
            maxLength = qMax(maxLength, cellText.length());
        }

        ui->partnertableWidget->setColumnWidth(col, qMax(maxLength * 10, 100));
    }
}

void PartnerTableWidget::on_insertButton_clicked()
{
    emit playMenuSound();
    PartnerTableInsertWindow *insertWindow = new PartnerTableInsertWindow(this);
    connect(insertWindow, &PartnerTableInsertWindow::dataInserted, this, &PartnerTableWidget::onDataInserted);
    insertWindow->show();
}

void PartnerTableWidget::on_deleteButton_clicked()
{
    emit playMenuSound();
    int currentRow = ui->partnertableWidget->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Ошибка", "Выберите строку для удаления!");
        return;
    }

    QString name = ui->partnertableWidget->item(currentRow, 1)->text();

    // Окно подтверждения удаления
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удалить строку?", "Удалить строку: " + name + "?", QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel) {
        emit playExitSound();
        return;
    }

    QTableWidgetItem *idItem = ui->partnertableWidget->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::critical(this, "Ошибка", "Не удалось получить ID выбранной строки!");
        return;
    }

    QString id = idItem->text();

    QSqlQuery query;
    query.prepare("DELETE FROM partnerTable WHERE id = :id");
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

void PartnerTableWidget::on_closeButton_clicked()
{
    emit playExitSound();
    emit closeOptions();
}

void PartnerTableWidget::on_editButton_clicked()
{
    emit playMenuSound();
    int selectedRow = ui->partnertableWidget->currentRow();
    if (selectedRow >= 0) {
        QString id = ui->partnertableWidget->item(selectedRow, 0)->text();
        QString name = ui->partnertableWidget->item(selectedRow, 1)->text();
        QString role = ui->partnertableWidget->item(selectedRow, 2)->text();
        QString contactPerson = ui->partnertableWidget->item(selectedRow, 3)->text();
        QString phone = ui->partnertableWidget->item(selectedRow, 4)->text();
        QString email = ui->partnertableWidget->item(selectedRow, 5)->text();

        PartnerTableInsertWindow *editWindow = new PartnerTableInsertWindow(this);
        editWindow->setDataForEditing(id, name, role, contactPerson, phone, email);
        connect(editWindow, &PartnerTableInsertWindow::dataInserted, this, &PartnerTableWidget::onDataInserted);
        editWindow->show();
    } else {
        QMessageBox::warning(this, "Внимание", "Пожалуйста, выберите строку для редактирования.");
    }
}

void PartnerTableWidget::onDataInserted()
{
    loadTableData();
}

void PartnerTableWidget::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton, ui->deleteButton, ui->editButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void PartnerTableWidget::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton, ui->deleteButton, ui->editButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void PartnerTableWidget::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton, ui->deleteButton, ui->editButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void PartnerTableWidget::updateTextColor()
{
    QList<QPushButton *> buttons = {ui->closeButton, ui->insertButton, ui->deleteButton, ui->editButton};
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

void PartnerTableWidget::updateLabel(const QColor &color) {

}
