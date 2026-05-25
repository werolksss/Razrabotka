#include "catalogwindow.h"
#include "ui_catalogwindow.h"
#include "orderwindow.h"

#include <QMessageBox>
#include <QPixmap>
#include <QPainter>

CatalogWindow::CatalogWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CatalogWindow)
    , orderWindow(nullptr)
    , currentProductIndex(0)
{
    ui->setupUi(this);

    fillProducts();

    for (const Product &product : products) {
        ui->productList->addItem(product.name);
    }

    if (!products.isEmpty()) {
        ui->productList->setCurrentRow(0);
        updateProductInfo(products[0]);
    }

    connect(ui->productList, &QListWidget::currentRowChanged,
            this, &CatalogWindow::showProductInfo);

    connect(ui->orderButton, &QPushButton::clicked,
            this, &CatalogWindow::openOrderWindow);

    connect(ui->backButton, &QPushButton::clicked,
            this, &CatalogWindow::goBack);
}

CatalogWindow::~CatalogWindow()
{
    delete orderWindow;
    delete ui;
}

void CatalogWindow::fillProducts()
{
    products.append({
        "Худи подростковое",
        "Мягкое стильное худи для прогулок, школы и повседневной носки.",
        1800,
        "Худи"
    });

    products.append({
        "Футболка для мальчика",
        "Удобная хлопковая футболка. Подходит для активных игр и прогулок.",
        900,
        "Футболка"
    });

    products.append({
        "Платье летнее",
        "Лёгкое красивое платье для девочки. Приятная ткань и аккуратный фасон.",
        1600,
        "Платье"
    });

    products.append({
        "Спортивный костюм",
        "Готовый образ для детского сада, прогулок и занятий спортом.",
        2400,
        "Костюм"
    });
}

void CatalogWindow::showProductInfo(int row)
{
    if (row < 0 || row >= products.size()) {
        return;
    }

    currentProductIndex = row;
    updateProductInfo(products[row]);
}

void CatalogWindow::updateProductInfo(const Product &product)
{
    ui->nameLabel->setText(product.name);
    ui->descriptionLabel->setText(product.description);
    ui->priceLabel->setText("Стоимость: " + QString::number(product.price) + " руб.");

    QPixmap pixmap(260, 180);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 22, QFont::Bold));
    painter.drawRect(0, 0, 259, 179);
    painter.drawText(pixmap.rect(), Qt::AlignCenter, product.photoText);
    painter.end();

    ui->photoLabel->setPixmap(pixmap);
}

void CatalogWindow::openOrderWindow()
{
    if (products.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите товар.");
        return;
    }

    Product selectedProduct = products[currentProductIndex];

    if (orderWindow != nullptr) {
        delete orderWindow;
    }

    orderWindow = new OrderWindow(selectedProduct, this);

    connect(orderWindow, &OrderWindow::orderFinished,
            this, [this]() {
                orderWindow->hide();
                this->hide();
                emit backToMain();
            });

    connect(orderWindow, &OrderWindow::backToCatalog,
            this, [this]() {
                orderWindow->hide();
                this->show();
            });

    orderWindow->show();
    this->hide();
}

void CatalogWindow::goBack()
{
    emit backToMain();
}
