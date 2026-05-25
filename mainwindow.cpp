#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "catalogwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , catalogWindow(nullptr)
{
    ui->setupUi(this);

    connect(ui->catalogButton, &QPushButton::clicked,
            this, &MainWindow::openCatalog);
}

MainWindow::~MainWindow()
{
    delete catalogWindow;
    delete ui;
}

void MainWindow::openCatalog()
{
    if (catalogWindow == nullptr) {
        catalogWindow = new CatalogWindow(this);

        connect(catalogWindow, &CatalogWindow::backToMain,
                this, [this]() {
                    catalogWindow->hide();
                    this->show();
                });
    }

    catalogWindow->show();
    this->hide();
}
