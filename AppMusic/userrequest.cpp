#include "userrequest.h"
#include <QtCore/QDebug>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include<QDebug>

UserRequest::UserRequest(QObject *parent):
    QThread(parent)
{

}

void UserRequest::getUserName(socketConnection* connection)
{

    QUrl u ("https://api.spotify.com/v1/me");

    auto reply = connection->getAutentication()->get(u);
    qDebug().nospace() << qPrintable(connection->getAutentication()->accessTokenUrl().toString());

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            reply->errorString();
            qInfo( "on Error get user" );
            return;
        }

        QString data = (QString)reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject root = document.object();

        emit updateUser(root["display_name"].toString());

        qInfo( "Get user success" );

        reply->deleteLater();
    });

}

/*void socketConnection::getPlaylist()
{
    if (userName.length() == 0) return;

    //ui->teOutput->appendPlainText("Loading Playlists ...");

    QUrl u ("https://api.spotify.com/v1/users/" + this->userName + "/playlists");

    auto reply = spotify.get(u);

    connect (reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            reply->errorString();
            qInfo( "On error user request:" );

            return;
        }

        const auto data = reply->readAll();

        reply->deleteLater();
    });

}*/
