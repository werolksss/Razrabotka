#include "orderwindow.h"
#include "ui_orderwindow.h"

#include <QMessageBox>

OrderWindow::OrderWindow(const Product &product, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OrderWindow)
    , selectedProduct(product)
{
    ui->setupUi(this);

    ui->productNameLabel->setText(selectedProduct.name);
    ui->descriptionLabel->setText(selectedProduct.description);
    ui->priceLabel->setText("Стоимость: " + QString::number(selectedProduct.price) + " руб.");

    connect(ui->confirmButton, &QPushButton::clicked,
            this, &OrderWindow::confirmOrder);

    connect(ui->backButton, &QPushButton::clicked,
            this, &OrderWindow::goBack);
}

OrderWindow::~OrderWindow()
{
    delete ui;
}

void OrderWindow::confirmOrder()
{
    QString customerName = ui->customerNameEdit->text().trimmed();
    QString phone = ui->phoneEdit->text().trimmed();

    if (customerName.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя и телефон.");
        return;
    }

    QMessageBox::information(
        this,
        "Заказ оформлен",
        "Спасибо, " + customerName + "!\n\n"
        "Ваш заказ оформлен:\n" +
        selectedProduct.name + "\n" +
        "Стоимость: " + QString::number(selectedProduct.price) + " руб.\n\n"
        "После оформления заказа выполняется переход на первую форму."
    );

    emit orderFinished();
}

void OrderWindow::goBack()
{
    emit backToCatalog();
}
