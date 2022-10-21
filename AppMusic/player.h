#ifndef PLAYER_H
#define PLAYER_H

#include <QList>
#include <track.h>

class Player
{
private:
    QList<Track> list_search = QList<Track>();
    QList<Track> list_player = QList<Track>();
    Track currentTrack = Track();
    int index_current_track = 0;
    QMediaPlayer *audio;

public:
    Player();
    QList<Track> getList_player() const;
    void setList_player(QList<Track> newList_player);
    Track getCurrentTrack() const;
    void setCurrentTrack(int index);
    QList<Track> getList_search() const;
    void setList_search(QList<Track> newList_search);

    Track* nextTrack();
    Track* previousTrack();

    bool hasNextTrack();
    bool hasPreviousTrack();
    QMediaPlayer *getAudio() const;
    void setAudio(QByteArray *data);
};

#endif // PLAYER_H
