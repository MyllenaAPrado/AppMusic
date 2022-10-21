#ifndef PLAYERREQUEST_H
#define PLAYERREQUEST_H

#include <QThread>
#include <socketconnection.h>
#include <track.h>

class PlayerRequest: public QThread
{
    Q_OBJECT
public:
    explicit PlayerRequest(QObject *parent =0);
    void stop();
    void getImage(socketConnection* connection, QUrl url_image);
    void getAudio(socketConnection* connection, QString id);
    void getTrackPreview(socketConnection* connection, QString url);

signals:
    void updateImage(QImage *image);
    void updateAudio(QByteArray data);

};

#endif // PLAYERREQUEST_H
