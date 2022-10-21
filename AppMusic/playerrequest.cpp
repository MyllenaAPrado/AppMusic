#include "playerrequest.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImage>
#include <QtMultimedia/QMediaPlayer>
#include <QBuffer>


PlayerRequest::PlayerRequest(QObject *parent):
    QThread(parent)
{

}

void PlayerRequest::getImage(socketConnection* connection, QUrl url_image)
{
    auto reply = connection->getAutentication()->get(url_image);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            reply->errorString();
            qInfo( "on Error get image" );
            return;
        }

        QByteArray data = (QByteArray)reply->readAll();
        QImage *image = new QImage();
        image->loadFromData(data);

        emit updateImage(image);

        qInfo( " Get image" );

        reply->deleteLater();
    });

}

void PlayerRequest::getAudio(socketConnection* connection, QString id)
{
    QUrl url_track = QUrl("https://api.spotify.com/v1/tracks/" + id);
    auto reply = connection->getAutentication()->get(url_track);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            reply->errorString();
            qInfo( "on Error get audio" );
            return;
        }


        QString data = (QString)reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject root = document.object();
        QString url_preview_song = root.value("preview_url").toString();

        reply->deleteLater();
        getTrackPreview(connection, url_preview_song);
    });

}

void PlayerRequest::getTrackPreview(socketConnection* connection, QString url)
{
    auto reply = connection->getAutentication()->get(url);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            reply->errorString();
            qInfo( "on Error get preview audio" );

            return;
        }

        QByteArray data = (QByteArray)reply->readAll();
        emit updateAudio(data);
        reply->deleteLater();
    });

}


/*
        qDebug() << data;
        QMediaPlayer *player = new QMediaPlayer();
        QBuffer *buffer = new QBuffer(player);
        buffer->setData(data);
        buffer->open(QIODevice::ReadOnly);
        qInfo( "Get Audio" );
        //player->setMedia(QMediaContent(),&buffer);
        emit updateAudio("Player");
*/
