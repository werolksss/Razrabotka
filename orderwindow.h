#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QMainWindow>

#include "product.h"

namespace Ui {
class OrderWindow;
}

class OrderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrderWindow(const Product &product, QWidget *parent = nullptr);
    ~OrderWindow();

signals:
    void orderFinished();
    void backToCatalog();

private slots:
    void confirmOrder();
    void goBack();

private:
    Ui::OrderWindow *ui;
    Product selectedProduct;
};

#endif // ORDERWINDOW_H
