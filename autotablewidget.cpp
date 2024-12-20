#include "autotablewidget.h"
#include "autotableinsertwindow.h"
#include "ui_autotablewidget.h"
#include "rentwindow.h"

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

    for (int row = 0; row < rowCount; ++row) {
        QString status = model->data(model->index(row, 6)).toString();
        QColor rowColor;

        // Set row color based on status
        if (status == "В АРЕНДЕ") {
            rowColor = QColor(Qt::blue);
        } else if (status == "Не подлежит восстановлению" || status == "Разбита" || status == "Неисправна") {
            rowColor = QColor(Qt::red);
        } else if(status == "Требует ремонта") {
            rowColor = QColor("#ff7f00");
        }else {
            rowColor = QColor("#2d2d2d");
        }

        for (int col = 0; col < columnCount; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QTableWidgetItem *item = ui->autoTableWidget_2->item(row, col);

            if (!item) {
                item = new QTableWidgetItem(data);
                ui->autoTableWidget_2->setItem(row, col, item);
            } else {
                item->setText(data);
            }

            item->setTextAlignment(Qt::AlignCenter);
            item->setBackground(rowColor);
            item->setFont(QFont("Arial", 10));
        }
    }

    ui->autoTableWidget_2->setColumnWidth(0, 50);
    ui->autoTableWidget_2->horizontalHeader()->resizeSection(0, 50);

    for (int col = 1; col < columnCount; ++col) {
        int maxLength = 0;

        QString headerText = ui->autoTableWidget_2->horizontalHeaderItem(col)->text();
        maxLength = qMax(maxLength, headerText.length());

        for (int row = 0; row < rowCount; ++row) {
            QString cellText = ui->autoTableWidget_2->item(row, col)->text();
            maxLength = qMax(maxLength, cellText.length());
        }

        ui->autoTableWidget_2->setColumnWidth(col, qMax(maxLength * 10, 100));
    }
}


void AutoTableWidget::updateButtonColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui-> rentButton, ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};
    for (QPushButton *button : buttons) {
        QPalette palette = button->palette();
        palette.setColor(QPalette::Button, color);
        button->setPalette(palette);
    }
    updateTextColor();
}

void AutoTableWidget::updateButtonFontColor(const QColor &color) {
    QList<QPushButton *> buttons = {ui-> rentButton, ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};
    for (QPushButton *button : buttons) {
        QPalette buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, color);
        button->setPalette(buttonPalette);
    }
}

void AutoTableWidget::updateButtonHeight(int height) {
    QList<QPushButton *> buttons = {ui-> rentButton, ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};

    for (QPushButton *button : buttons) {
        button->setFixedHeight(height);
    }
}

void AutoTableWidget::updateTextColor()
{
    QList<QPushButton *> buttons = {ui-> rentButton, ui->insertButton, ui->closeButton, ui->editButton, ui->deleteButton};

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

void AutoTableWidget::on_rentButton_clicked() {
    int currentRow = ui->autoTableWidget_2->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Ошибка", "Выберите авто!");
        return;
    }

    QString status = ui->autoTableWidget_2->item(currentRow, 6)->text();
    QString autoName = ui->autoTableWidget_2->item(currentRow, 1)->text();
    if(status == "В АРЕНДЕ") {
        QMessageBox::critical(this, "Ошибка", "Авто уже в аренде!");
        return;
    }
    if(status == "Разбита" || status == "Неисправна" || status == "Не подлежит восстановлению") {
        QMessageBox::critical(this, "Ошибка", "Авто в непригодном состоянии!");
        return;
    }

    emit playMenuSound();

    QString autoId = ui->autoTableWidget_2->item(currentRow, 0)->text();
    QString costPerHour = ui->autoTableWidget_2->item(currentRow, 7)->text();
    QString costPerDay = ui->autoTableWidget_2->item(currentRow, 8)->text();

    RentWindow *rentWindow = new RentWindow(this);
    rentWindow->autoId = autoId;
    rentWindow->setAutoName(autoName);
    rentWindow->setWindowTitle("Расчет аренды авто");
    rentWindow->setCostPerHour(costPerHour.toDouble());
    rentWindow->setCostPerDay(costPerDay.toDouble());

    connect(rentWindow, &RentWindow::updateAutoStatus, this, &AutoTableWidget::updateAutoStatus);
    rentWindow->show();
}

void AutoTableWidget::on_insertButton_clicked()
{
    emit playMenuSound();
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

    emit playMenuSound();
    QString name = ui->autoTableWidget_2->item(currentRow, 1)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удалить строку?", "Удалить строку: " + name + "?", QMessageBox::Ok | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel) {
        emit playExitSound();
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
        loadTableData();
    }
}

void AutoTableWidget::on_editButton_clicked()
{
    emit playMenuSound();
    int currentRow = ui->autoTableWidget_2->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Ошибка", "Выберите строку для редактирования!");
        return;
    }

    QString id = ui->autoTableWidget_2->item(currentRow, 0)->text();
    QString name = ui->autoTableWidget_2->item(currentRow, 1)->text();
    QString year = ui->autoTableWidget_2->item(currentRow, 2)->text();
    QString mileage = ui->autoTableWidget_2->item(currentRow, 3)->text();
    QString transmission = ui->autoTableWidget_2->item(currentRow, 4)->text();
    QString wheelSide = ui->autoTableWidget_2->item(currentRow, 5)->text();
    QString status = ui->autoTableWidget_2->item(currentRow, 6)->text();
    QString costPerHour = ui->autoTableWidget_2->item(currentRow, 7)->text();
    QString costPerDay = ui->autoTableWidget_2->item(currentRow, 8)->text();

    AutoTableInsertWindow *insertWindow = new AutoTableInsertWindow(this);
    insertWindow->setWindowTitle("Редактировать авто");

    insertWindow->setDataForEditing(id, name, year, mileage, transmission, wheelSide, status, costPerHour, costPerDay);

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

void AutoTableWidget::updateAutoStatus(QString id, const QString &status)
{
    QSqlQuery query;
    query.prepare("UPDATE autoTable SET status = :status WHERE id = :id");
    query.bindValue(":status", status);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Ошибка обновления статуса авто:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка обновления статуса авто: " + query.lastError().text());
    } else {
        qDebug() << "Статус авто успешно обновлен!";
        loadTableData();
    }
}
