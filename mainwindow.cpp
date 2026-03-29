#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SHA256.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString password = ui->lineEdit->text();
    std::string hash = MD5(password)
    ui->label->setText(QString::fromStdString(hash));
}
