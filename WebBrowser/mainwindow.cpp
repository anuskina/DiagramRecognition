#include    "mainwindow.h"
#include    "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete  ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString urlTogo =   this->ui->lineEdit->text();
    this->ui->webView->load(QUrl(urlTogo));
}
