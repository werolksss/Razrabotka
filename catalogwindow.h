#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "product.h"

namespace Ui {
class CatalogWindow;
}

class OrderWindow;

class CatalogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent = nullptr);
    ~CatalogWindow();

signals:
    void backToMain();

private slots:
    void showProductInfo(int row);
    void openOrderWindow();
    void goBack();

private:
    void fillProducts();
    void updateProductInfo(const Product &product);

private:
    Ui::CatalogWindow *ui;
    QVector<Product> products;
    OrderWindow *orderWindow;
    int currentProductIndex;
};

#endif // CATALOGWINDOW_H
