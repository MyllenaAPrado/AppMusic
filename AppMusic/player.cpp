#include "player.h"
#include <QBuffer>
#include <QMediaPlayer>
#include <QtMultimedia>

Player::Player()
{
}

QList<Track> Player::getList_player() const
{
    return list_player;
}

void Player::setList_player(QList<Track> newList_player)
{
    list_player = newList_player;
}

Track Player::getCurrentTrack() const
{
    return currentTrack;
}

void Player::setCurrentTrack(int index)
{
    this->index_current_track = index;
    currentTrack = this->list_player.at(index);
}

QList<Track> Player::getList_search() const
{
    return list_search;
}

void Player::setList_search(QList<Track> newList_search)
{
    list_search = newList_search;
}

Track* Player::nextTrack()
{
    int next = this->index_current_track +1;
    if(next > this->list_player.size()){
        return NULL;
    }
    this->index_current_track = next;
    this->currentTrack = this->list_player.at(next);
    return &this->currentTrack;

}

Track* Player::previousTrack()
{
    int previous = this->index_current_track -1;
    if(previous < 0){
        return NULL;
    }
    this->index_current_track = previous;
    this->currentTrack = this->list_player.at(previous);
    return &this->currentTrack;
}

bool Player::hasNextTrack()
{
    int next = this->index_current_track +1;
    if(next >= this->list_player.size()){
        return false;
    }
    return true;
}

bool Player::hasPreviousTrack()
{
    int previous = this->index_current_track -1;
    if(previous < 0){
        return false;
    }
    return true;
}

QMediaPlayer *Player::getAudio() const
{
    return audio;
}

void Player::setAudio(QByteArray *data)
{
    /*
   QBuffer mediaStream(data);
   this->audio = player;
   this->audio->setMedia(QMediaContent(), &buffer);
   this->audio-play();
   QBuffer *buffer = new QBuffer(player);
   buffer->setData(arr);
   buffer->open(QIODevice::ReadOnly);

   player->setMedia(QMediaContent(),buffer);
   audio = newAudio;*/
}


/*QFile file(R"(C:\test.mp3)");    // sound dir
    file.open(QIODevice::ReadOnly);
    QByteArray arr = file.readAll();

    QMediaPlayer *player = new QMediaPlayer(&a);

    QBuffer *buffer = new QBuffer(player);
    buffer->setData(arr);
    buffer->open(QIODevice::ReadOnly);

    player->setMedia(QMediaContent(),buffer);

    player->play();*/
