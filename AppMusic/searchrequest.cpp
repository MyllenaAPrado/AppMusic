#include "searchrequest.h"
#include <QtCore/QDebug>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include<QDebug>
#include <playerrequest.h>

SearchRequest::SearchRequest(QObject *parent):
    QThread(parent)
{

}

void SearchRequest::searchMusic(socketConnection* connection, QString search_text)
{
    QUrl url ("https://api.spotify.com/v1/search?type=track&q="+ search_text);
    auto reply = connection->getAutentication()->get(url);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            reply->errorString();
            qDebug().nospace() << qPrintable(reply->errorString());

            qInfo( "on Error search " );
             QString data = (QString)reply->readAll();
             qDebug().nospace() << qPrintable(data);
            return;
        }

        QString data = (QString)reply->readAll();
        parseJsonSearchResult(data);

        emit updateSearch(this->list_tracks);

        reply->deleteLater();
    });
}

void SearchRequest::parseJsonSearchResult(QString data)
{
    this->list_tracks->clear();
    PlayerRequest player_request = PlayerRequest();

    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());

    QJsonObject root = document.object();
    QJsonObject track = root.value("tracks").toObject();

    QJsonArray items = track.value("items").toArray();

    for (auto item : items) {

        QJsonObject element = item.toObject();
        Track *track = new Track();

        track->setName(element.value("name").toString());
        track->setId(element.value("id").toString());
        track->setHref(element.value("href").toString());
        track->setId_track(element.value("id").toString());

        QJsonArray artist_array = element.value("artists").toArray();
        track->setArtist(artist_array.at(0).toObject().value("name").toString());

        QJsonObject album = element.value("album").toObject();        
        QJsonArray images = album.value("images").toArray();
        QJsonObject image = images.at(1).toObject();
        track->setImage_url(image.value("url").toString());
        track->setHeight(image.value("height").toInt());
        track->setWidth(image.value("width").toInt());
        this->list_tracks->append(*track);

    }
}

