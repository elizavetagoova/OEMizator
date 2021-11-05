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
    ConnectionInfo m_connectionInfo;
    void sendRequest(const ConnectionInfo& m_connectionInfo);
    void makeRequest();

public slots:
    void onFinished(QNetworkReply *reply);

private:

    QNetworkAccessManager *m_networkAccessManager;
};

#endif // OEMCHECKER_H
