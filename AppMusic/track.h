#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QUrl>
#include <QImage>
#include <QString>
#include <QtMultimedia/QMediaPlayer>

class Track
{
private:
    QString name;
    QString id;
    QString artist;
    QUrl href;
    QUrl image_url;
    qint16 height;
    qint16 width;
    QImage image;
    QString id_track;

public:
    Track();

    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getId() const;
    void setId(const QString &newId);
    const QString &getArtist() const;
    void setArtist(const QString &newArtist);
    const QUrl &getHref() const;
    void setHref(const QUrl &newHref);
    const QUrl &getImage_url() const;
    void setImage_url(const QUrl &newImage_url);
    qint16 getHeight() const;
    void setHeight(qint16 newHeight);
    qint16 getWidth() const;
    void setWidth(qint16 newWidth);
    const QImage &getImage() const;
    void setImage(const QImage &newImage);
    const QString &getId_track() const;
    void setId_track(const QString &newId_track);
};

#endif // TRACK_H
