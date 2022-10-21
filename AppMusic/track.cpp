#include "track.h"

const QString &Track::getName() const
{
    return name;
}

void Track::setName(const QString &newName)
{
    name = newName;
}

const QString &Track::getId() const
{
    return id;
}

void Track::setId(const QString &newId)
{
    id = newId;
}

const QString &Track::getArtist() const
{
    return artist;
}

void Track::setArtist(const QString &newArtist)
{
    artist = newArtist;
}

const QUrl &Track::getHref() const
{
    return href;
}

void Track::setHref(const QUrl &newHref)
{
    href = QUrl(newHref);
}

const QUrl &Track::getImage_url() const
{
    return image_url;
}

void Track::setImage_url(const QUrl &newImage_url)
{
    image_url = QUrl(newImage_url);
}

qint16 Track::getHeight() const
{
    return height;
}

void Track::setHeight(qint16 newHeight)
{
    height = newHeight;
}

qint16 Track::getWidth() const
{
    return width;
}

void Track::setWidth(qint16 newWidth)
{
    width = newWidth;
}

const QImage &Track::getImage() const
{
    return image;
}

void Track::setImage(const QImage &newImage)
{
    image = newImage;
}

const QString &Track::getId_track() const
{
    return id_track;
}

void Track::setId_track(const QString &newId_track)
{
    id_track = newId_track;
}

Track::Track()
{
}
