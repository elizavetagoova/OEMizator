#ifndef OEMCHECKER_H
#define OEMCHECKER_H

#include <QtNetwork>
#include <QUrl>

struct ConnectionInfo {
    QString ip;
    QString login;
    QString pass;
};

class Oemchecker : public QObject
{
    Q_OBJECT

public:
    Oemchecker();
    void setConnectionInfo(QString ip, QString login, QString pass);
    void startCheck();
    void sendRequest();

public slots:
    void onFinished(QNetworkReply *reply);    

private:
    QNetworkAccessManager *m_networkAccessManager;
    ConnectionInfo m_connectionInfo;
    QString m_currentBrand;
    QJsonArray m_requests;
    int m_index;

signals:
    void recievedResponse(QString str, int errorCode);
};

#endif // OEMCHECKER_H
