#include "autoTableWidget.h"
#include "autotableinsertwindow.h"
#include "ui_autoTableWidget.h"

AutoTableWidget::AutoTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoTableWidget)
{
    ui->setupUi(this);
    setupDatabase();
    loadTableData();
}

AutoTableWidget::~AutoTableWidget()
{
    delete ui;
}

void AutoTableWidget::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("471979");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    } else {
        qDebug() << "Подключение успешно!!! (AutoTableWidget)";
    }
}

void AutoTableWidget::loadTableData()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id, name, year, mileage, transmission, wheel_side, status, cost_per_hour, cost_per_day FROM autoTable", db);

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

    ui->autoTableWidget_2->clearContents();
    ui->autoTableWidget_2->setRowCount(rowCount);
    ui->autoTableWidget_2->setColumnCount(columnCount);

    // Устанавливаем заголовки столбцов
    // ui->autoTableWidget_2->setHorizontalHeaderLabels({"ID", "Название", "Год", "Пробег", "Трансмиссия", "Сторона руля", "Статус", "Цена за час", "Цена за день"});

    // Заполняем таблицу данными
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QTableWidgetItem *item = new QTableWidgetItem(data);
            item->setTextAlignment(Qt::AlignCenter);
            ui->autoTableWidget_2->setItem(row, col, item);
        }
    }

    // Устанавливаем ширину первого столбца
    ui->autoTableWidget_2->setColumnWidth(0, 50);  // Устанавливаем ширину первого столбца на 50 пикселей
    ui->autoTableWidget_2->horizontalHeader()->resizeSection(0, 50); // Ограничиваем ширину заголовка первого столбца

    // Устанавливаем ширину для остальных столбцов в зависимости от содержимого
    for (int col = 1; col < columnCount; ++col) {
        int maxLength = 0;

        // Проверяем заголовок
        QString headerText = ui->autoTableWidget_2->horizontalHeaderItem(col)->text();
        maxLength = qMax(maxLength, headerText.length());

        // Проверяем все строки в этом столбце
        for (int row = 0; row < rowCount; ++row) {
            QString cellText = ui->autoTableWidget_2->item(row, col)->text();
            maxLength = qMax(maxLength, cellText.length());
        }

        // Устанавливаем ширину столбца в соответствии с максимальной длиной
        ui->autoTableWidget_2->setColumnWidth(col, qMax(maxLength * 10, 100));  // Умножаем на коэффициент для корректной ширины
    }
}


/* for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QTableWidgetItem *item = new QTableWidgetItem(data);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, col, item);
        }
    } */

void AutoTableWidget::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void AutoTableWidget::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void AutoTableWidget::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void AutoTableWidget::updateTextColor()
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

void AutoTableWidget::updateLabel(const QColor &color) {

}

void AutoTableWidget::on_insertButton_clicked()
{
    AutoTableInsertWindow *insertWindow = new AutoTableInsertWindow(this);
    connect(insertWindow, &AutoTableInsertWindow::dataInserted, this, &AutoTableWidget::loadTableData);
    insertWindow->show();
}

void AutoTableWidget::on_deleteButton_clicked()
{
    int currentRow = ui->autoTableWidget_2->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Ошибка", "Выберите строку для удаления!");
        return;
    }

    // Получаем название автомобиля из выбранной строки
    QString name = ui->autoTableWidget_2->item(currentRow, 1)->text();

    // Окно подтверждения удаления
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удалить строку?", "Удалить строку: " + name + "?", QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel) {
        return;
    }

    QTableWidgetItem *idItem = ui->autoTableWidget_2->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::critical(this, "Ошибка", "Не удалось получить ID выбранной строки!");
        return;
    }

    QString id = idItem->text();

    QSqlQuery query;
    query.prepare("DELETE FROM autoTable WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления данных:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка удаления данных: " + query.lastError().text());
    } else {
        qDebug() << "Данные успешно удалены!";
        QMessageBox::information(this, "Успех", "Авто успешно удалено!");
        loadTableData(); // Обновляем данные таблицы после удаления
    }
}

void AutoTableWidget::on_editButton_clicked()
{
    int currentRow = ui->autoTableWidget_2->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Ошибка", "Выберите строку для редактирования!");
        return;
    }

    // Получаем данные выбранной строки
    QString id = ui->autoTableWidget_2->item(currentRow, 0)->text();
    QString name = ui->autoTableWidget_2->item(currentRow, 1)->text();
    QString year = ui->autoTableWidget_2->item(currentRow, 2)->text();
    QString mileage = ui->autoTableWidget_2->item(currentRow, 3)->text();
    QString transmission = ui->autoTableWidget_2->item(currentRow, 4)->text();
    QString wheelSide = ui->autoTableWidget_2->item(currentRow, 5)->text();
    QString status = ui->autoTableWidget_2->item(currentRow, 6)->text();
    QString costPerHour = ui->autoTableWidget_2->item(currentRow, 7)->text();
    QString costPerDay = ui->autoTableWidget_2->item(currentRow, 8)->text();

    // Открываем окно редактирования с предзаполненными данными
    AutoTableInsertWindow *insertWindow = new AutoTableInsertWindow(this);
    insertWindow->setWindowTitle("Редактировать авто");

    // Передаем данные в форму редактирования
    insertWindow->setDataForEditing(id, name, year, mileage, transmission, wheelSide, status, costPerHour, costPerDay);

    // Подключаем сигнал для обновления таблицы
    connect(insertWindow, &AutoTableInsertWindow::dataInserted, this, &AutoTableWidget::loadTableData);

    insertWindow->show();
}

void AutoTableWidget::on_closeButton_clicked()
{
    emit playExitSound();
    emit closeOptions();
}

void AutoTableWidget::onDataInserted()
{
    loadTableData();
}
