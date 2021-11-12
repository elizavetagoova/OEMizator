#include "oemchecker.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>

Oemchecker::Oemchecker()
    : m_index(0)
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &Oemchecker::onFinished);
}

void Oemchecker::setConnectionInfo(const ConnectionInfo& connInfo)
{
    m_connectionInfo.ip = connInfo.ip;
    m_connectionInfo.login = connInfo.login;
    m_connectionInfo.pass = connInfo.pass;
}

void Oemchecker::startCheck()
{
    QFile file("requests.json");
    if (!file.exists())
    {
        emit errorOcured("config file is missing");
        return;
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (!file.isOpen())
    {
        emit errorOcured(file.fileName() + " is not open!");
        return;
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError errorParsing;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &errorParsing);
    if (errorParsing.error != 0)
    {
        emit errorOcured(errorParsing.errorString());
        return;
    }

    QJsonObject json = doc.object();
    m_requests = json["All"].toArray();

    sendRequest();
}

void Oemchecker::onFinished(QNetworkReply *reply)
{
    int errorCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();    
    emit recieveResponse(m_currentBrand, errorCode);

    if(m_index < m_requests.size())
    {
        sendRequest();
    }
    else
    {
        emit checkIsFinished();
        m_index = 0;
    }
}

void Oemchecker::sendRequest()
{
    QJsonObject brandItem = m_requests[m_index++].toObject();
    QJsonObject request = brandItem["Requests"].toObject();
    QString path = request["Path"].toString();
    m_currentBrand = brandItem["BrandName"].toString();

    QUrl url("http://" + m_connectionInfo.ip + path);
    url.setUserName(m_connectionInfo.login);
    url.setPassword(m_connectionInfo.pass);

    m_networkAccessManager.get(QNetworkRequest(url));
}


