#include "oemchecker.h"
#include <QMessageBox>

Oemchecker::Oemchecker()
{
    m_networkAccessManager = new QNetworkAccessManager();
    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, &Oemchecker::onFinished);
}

void Oemchecker::onFinished(QNetworkReply *reply)
{
//    QString str = reply->readAll();
//    QMessageBox msgBox;
//    msgBox.setText(str);
//    msgBox.exec();
//    qDebug() << str;
}
void Oemchecker::sendRequest(QString ip, QString login, QString pass)
{
    QUrl url("http://" + ip + "/cgi-bin/magicBox.cgi?action=getDeviceType");
    url.setUserName(login);
    url.setPassword(pass);
    m_networkAccessManager->get(QNetworkRequest(url));
}
