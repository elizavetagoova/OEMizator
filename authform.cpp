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
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::on_OKpushButton_clicked()
{
    m_connectionInfo.ip = ui->IPlineEdit->text();
    m_connectionInfo.login = ui->LOGINlineEdit->text();
    m_connectionInfo.pass = ui->PASSlineEdit->text();

    ui->OKpushButton->setText("In progress");

    ui->listWidget->setEnabled(true);

//    ui->listWidget->addItem("ONVIF");
//    ui->listWidget->addItem("ONVIF");
//    ui->listWidget->addItem("ONVIF");
//    ui->listWidget->addItem("ONVIF");
//    ui->listWidget->addItem("ONVIF");
//    ui->listWidget->addItem("ONVIF");
//    ui->listWidget->addItem("ONVIF");
//    ui->listWidget->item
//    ui->listWidget->item(ui->listWidget->count()-1)->setForeground(Qt::blue);
//    ui->listWidget->addItem(&item);
//    ui->listWidget->addItem("ZALIMKHANCHIK");
    m_checker.makeRequest();
    m_checker.sendRequest(m_connectionInfo);
}
