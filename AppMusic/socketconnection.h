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
    QString clientId = "6c5544868a7f4d39bf9cb2bcd770134f";
    QString clientSecret = "f1dce1a6615a43d2ba2b3eea084cdd22";
};


#endif // SOCKETCONNECTION_H
