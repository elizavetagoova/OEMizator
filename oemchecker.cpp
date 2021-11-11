#include "oemchecker.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

Oemchecker::Oemchecker()
    : m_index(0)
{
    m_networkAccessManager = new QNetworkAccessManager();
    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, &Oemchecker::onFinished);
}

void Oemchecker::setConnectionInfo(QString ip, QString login, QString pass)
{
    m_connectionInfo.ip = ip;
    m_connectionInfo.login = login;
    m_connectionInfo.pass = pass;
}

void Oemchecker::startCheck()
{
    QFile file("requests.json");
    if (file.exists())
    {
        qDebug() << file.fileName();
        file.open(QIODevice::ReadOnly | QIODevice::Text);
    }
    else
    {
        qDebug() << "ERROR: config file is missing";
        return;
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(rawData);
    QJsonObject json = doc.object();
    m_requests = json["All"].toArray();

    sendRequest();
}

void Oemchecker::onFinished(QNetworkReply *reply)
{
    int errorCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();    
    emit recievedResponse(m_currentBrand, errorCode);

    if(m_index < m_requests.size())
    {
        sendRequest();
    }
    else
    {
        m_index = 0;
        QMessageBox msgBox;
        msgBox.setText("Check is done!");
        msgBox.exec();
    }
}

void Oemchecker::sendRequest()
{
    QJsonObject brandItem = m_requests[m_index++].toObject();
    QJsonObject request = brandItem["Requests"].toObject();
    QString path = request["Path"].toString();
    QString brand = brandItem["BrandName"].toString();
    m_currentBrand = brand;

    QUrl url("http://" + m_connectionInfo.ip + path);
    url.setUserName(m_connectionInfo.login);
    url.setPassword(m_connectionInfo.pass);

    m_networkAccessManager->get(QNetworkRequest(url));
}


