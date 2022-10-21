#include "socketconnection.h"
#include <QtCore/QDebug>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QAbstractOAuth>
#include <QVariantMap>

socketConnection::socketConnection()
{

    const QUrl redirectUri("http://127.0.0.1:8888/");

    const auto port = static_cast<quint16>(redirectUri.port());
    auto replyHandler = new QOAuthHttpServerReplyHandler(port, this);
    this->spotify.setReplyHandler(replyHandler);

    this->spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    this->spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));

    this->spotify.setClientIdentifier(clientId);
    this->spotify.setClientIdentifierSharedKey(clientSecret);
    //this->spotify.setScope("user-read-private user-top-read playlist-read-private playlist-modify-public playlist-modify-private");


    this->spotify.setModifyParametersFunction([](QAbstractOAuth::Stage stage, QMultiMap<QString, QVariant>* parameters) {
       // Percent-decode the "code" parameter so spotify can match it
       if (stage == QAbstractOAuth::Stage::RequestingAccessToken  || stage == QAbstractOAuth::Stage::RequestingAuthorization) {
          QByteArray code = parameters->value("redirect_uri").toByteArray();
          (*parameters).value("redirect_uri").setValue(QUrl::fromPercentEncoding(code));
          qInfo( "Enter" );
          qDebug() << QUrl::fromPercentEncoding(code);
       }
    });

    connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
            &QDesktopServices::openUrl);

    connect(&spotify, &QOAuth2AuthorizationCodeFlow::statusChanged,
            this, &socketConnection::onAuthStatusChanged);

    connect(&spotify, &QOAuth2AuthorizationCodeFlow::granted,
            this, &socketConnection::onGranted);
    connect(&spotify, &QOAuth2AuthorizationCodeFlow::error,
            this, &socketConnection::onError);

    qInfo( "create socket connection" );

}

void socketConnection::onAuthStatusChanged()
{
    qInfo( "onAuthStatusChanged" );
}

void socketConnection::onGranted()
{
    qInfo( "onGranted" );
    emit onGetUser();
}

void socketConnection::onError()
{
    qInfo( "onError" );
}

void socketConnection::grant()
{
     spotify.grant();
}

QOAuth2AuthorizationCodeFlow* socketConnection::getAutentication()
{
    return &spotify;
}





