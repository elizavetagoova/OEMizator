#include "oemchecker.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
//#include <QMessageBox>

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
void Oemchecker::sendRequest(const ConnectionInfo& connectionInfo)
{
    QUrl url("http://" + connectionInfo.ip + "/cgi-bin/magicBox.cgi?action=getDeviceType");
    url.setUserName(connectionInfo.login);
    url.setPassword(connectionInfo.pass);
    m_networkAccessManager->get(QNetworkRequest(url));
}

void Oemchecker::makeRequest()
{
    QString val;

    QFile file("requests.json");
    if (file.exists()) qDebug() << file.fileName();
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray rawData = file.readAll();
    //qDebug() << rawData;
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(rawData);
    QJsonObject json = doc.object();
    //QString str = json["CfgVersion"].toString();
    qDebug() << json["CfgVersion"];
//    bool t = json["t"].toBool();
//    qDebug() << t;
//    bool f = json["f"].toBool();
//    qDebug() << f;
//    bool n = json["n"].toBool();
//    int  i = json["i"].toInt();
//    double pi = json["pi"].toDouble();
//    QJsonArray ar = json["a"].toArray();
//    QList <QVariant> at = ar.toVariantList();
}
