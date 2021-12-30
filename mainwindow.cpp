#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QProcess"
#include "QMessageBox"
#include "iostream"
#include <unistd.h>

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


void MainWindow::on_pushButton_clicked()
{

    //check 4 root permissin
    auto myprivs = geteuid();

    if (myprivs != 0){
        QMessageBox::warning(this,"Warning","You are not running as root.");
        return;
    }

    //Get user who ran this program as root no matter user run this using su, sudo or pkexec.
    QString currentUser;  //Define a empty string to avoid unexpected crash
    QProcess getCurrentUser;
    //I don't know how to run command using QProcess::start();
    getCurrentUser.start("logname");
    getCurrentUser.waitForFinished();
    currentUser = getCurrentUser.readAllStandardOutput();
    if (currentUser.isEmpty()){
        QMessageBox::warning(this,"Warning","Unable to get user who ran this program as root.");
        return;
    }else{
        QMessageBox::information(this,"Info","Current user is "+currentUser);
    }

    //Okay,We gonna run Firefox using the current user.
    //Assuming your default web browser is firefox
    QProcess runFirefox;
    runFirefox.start("sudo -u " + currentUser + "xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    runFirefox.waitForFinished();

}

