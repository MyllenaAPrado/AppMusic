#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QOAuth2AuthorizationCodeFlow>

class socketConnection: public QObject
{
    Q_OBJECT
public:
    explicit socketConnection();
    void grant();
    QOAuth2AuthorizationCodeFlow* getAutentication();

signals:
    void onGetUser();

private slots:
    void onAuthStatusChanged();
    void onGranted();
    void onError();

private:
    QOAuth2AuthorizationCodeFlow spotify;
    QString clientId = "XXXXXXXXXXXXXXXXXXXXXXX";
    QString clientSecret = "XXXXXXXXXXXXXXXXXXXXXXX";
};


#endif // SOCKETCONNECTION_H
