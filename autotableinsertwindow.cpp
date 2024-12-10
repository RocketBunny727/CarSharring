#include "autotableinsertwindow.h"
#include "ui_autotableinsertwindow.h"

AutoTableInsertWindow::AutoTableInsertWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AutoTableInsertWindow)
{
    ui->setupUi(this);
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
    }
    else {
        qDebug() << "Подключение успешно!!! (AutoTableInsertWindow)";
    }
}

void AutoTableWidget::loadTableData()
{
    QSqlQuery query("SELECT *FROM public.autoTable");
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
        qDebug() << "Запрос: " << query.executedQuery();
        return;
    }

    ui->autoTableWidget_2->clearContents();
    ui->autoTableWidget_2->setRowCount(0);

    int colCount = query.record().count();
    ui->autoTableWidget_2->setColumnCount(colCount);

    int row = 0;
    while (query.next()) {
        ui->autoTableWidget_2->insertRow(row);
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->autoTableWidget_2->setItem(row, col, item);
        }
        row++;
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
        }
        else {
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
    emit playMenuSound();
}

