#include "authform.h"
#include "ui_authform.h"
#include <QString>
#include <QDebug>

AuthForm::AuthForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthForm)
{
    ui->setupUi(this);
    ui->listWidget->setDisabled(true);

    connect(&m_checker, &Oemchecker::recievedResponse, this, &AuthForm::onRecieveReply);

    ui->IPlineEdit->setText("172.19.9.50");
    ui->LOGINlineEdit->setText("root");
    ui->PASSlineEdit->setText("root");
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::on_OKpushButton_clicked()
{
    ui->listWidget->setEnabled(true);

    QString ip = ui->IPlineEdit->text();
    QString login = ui->LOGINlineEdit->text();
    QString pass = ui->PASSlineEdit->text();

    m_checker.setConnectionInfo(ip, login, pass);
    m_checker.startCheck();
}

void AuthForm::onRecieveReply(QString str, int errorCode)
{
    ui->listWidget->addItem(str);
    if (errorCode == 200)
    {
        ui->listWidget->item(ui->listWidget->count()-1)->setForeground(Qt::green);
    }
    else
    {
        ui->listWidget->item(ui->listWidget->count()-1)->setForeground(Qt::red);
    }
}
