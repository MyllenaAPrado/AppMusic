#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

#include <QThread>
#include <socketconnection.h>
#include <track.h>

class SearchRequest : public QThread
{
    Q_OBJECT

private:
    QList<Track> *list_tracks = new QList<Track>();
    void parseJsonSearchResult(QString data);

public:
    explicit SearchRequest(QObject *parent =0);
    void stop();
    void searchMusic(socketConnection* connection, QString search_text);

signals:
    void updateSearch(QList<Track> *result_list);
};

#endif // SEARCHREQUEST_H
