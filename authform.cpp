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
    QString ipStr = ui->IPlineEdit->text();
    QString loginStr = ui->LOGINlineEdit->text();
    QString passStr = ui->PASSlineEdit->text();

    ui->OKpushButton->setText("in progress");

    ui->listWidget->setEnabled(true);

    ui->listWidget->addItem("ONVIF");
    ui->listWidget->addItem("ONVIF");
    ui->listWidget->addItem("ONVIF");
    ui->listWidget->addItem("ONVIF");
    ui->listWidget->addItem("ONVIF");
    ui->listWidget->addItem("ONVIF");
    ui->listWidget->addItem("ONVIF");
    //ui->listWidget->item
    //ui->listWidget->item(ui->listWidget->count()-1)->setForeground(Qt::blue);
    //ui->listWidget->addItem(&item);
    //ui->listWidget->addItem("ZALIMKHANCHIK");
    m_auth.sendRequest(ipStr, loginStr, passStr);
}
