#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionopen_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(
                this, tr("Open Directory"), "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug() << dir;
    ui->checktreeview->setFolderPath(dir);
}

