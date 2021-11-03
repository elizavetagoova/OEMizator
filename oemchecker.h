#ifndef OEMCHECKER_H
#define OEMCHECKER_H

#include <QtNetwork>
#include <QUrl>

class Oemchecker : public QObject
{
    Q_OBJECT
public:
    Oemchecker();
    void sendRequest(QString ip, QString login, QString pass);

public slots:
    void onFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkAccessManager;
};

#endif // OEMCHECKER_H
