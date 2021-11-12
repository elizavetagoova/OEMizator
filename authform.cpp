#include "authform.h"
#include "ui_authform.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>

static const int EC_OK = 200;

AuthForm::AuthForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthForm)
{
    ui->setupUi(this);
    ui->listWidget->setDisabled(true);
    ui->CLEARButton->setDisabled(true);

    connect(&m_checker, &Oemchecker::recieveResponse, this, &AuthForm::onRecieveReply);
    connect(&m_checker, &Oemchecker::checkIsFinished, this, &AuthForm::onCheckIsFinished);
    connect(&m_checker, &Oemchecker::errorOcured, this, &AuthForm::onErrorOcured);
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::on_OKpushButton_clicked()
{
    ConnectionInfo connInfo;
    connInfo.ip = ui->IPlineEdit->text();
    connInfo.login = ui->LOGINlineEdit->text();
    connInfo.pass = ui->PASSlineEdit->text();

    if (connInfo.ip.isEmpty() || connInfo.login.isEmpty() || connInfo.pass.isEmpty())
    {
        onErrorOcured("connectionInfo is not valid!");
        return;
    }

    ui->listWidget->setEnabled(true);

    ui->OKpushButton->setText("IN PROGRESS");
    ui->OKpushButton->setEnabled(false);

    ui->IPlineEdit->setEnabled(false);
    ui->LOGINlineEdit->setEnabled(false);
    ui->PASSlineEdit->setEnabled(false);

    m_checker.setConnectionInfo(connInfo);
    m_checker.startCheck();
}

void AuthForm::onRecieveReply(QString str, int errorCode)
{
    ui->listWidget->addItem(str);
    ui->listWidget->item(ui->listWidget->count()-1)->setForeground(errorCode == EC_OK ? Qt::green : Qt::red);
}

void AuthForm::onCheckIsFinished()
{
    QMessageBox msgBox;
    msgBox.setText("Check is done!");
    msgBox.exec();

    ui->OKpushButton->setText("CHECK");
    ui->OKpushButton->setEnabled(true);

    ui->IPlineEdit->setEnabled(true);
    ui->LOGINlineEdit->setEnabled(true);
    ui->PASSlineEdit->setEnabled(true);

    ui->CLEARButton->setEnabled(true);
}

void AuthForm::onErrorOcured(QString error)
{
    QMessageBox msgBox;
    msgBox.setText("ERROR: " + error);
    msgBox.exec();
}

void AuthForm::on_CLEARButton_clicked()
{
    ui->listWidget->clear();
}
