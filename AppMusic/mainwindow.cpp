#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <itemsearchresult.h>
#include <QBuffer>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audio(new QMediaPlayer(this))
{
    ui->setupUi(this);
    this->audio = new QMediaPlayer(this);
    this->audioOutput = new QAudioOutput(this);

    //set initial icons
    setWindowIcon(QIcon("C:/Users/mylle/Documents/AppMusic/resources/musical-note.png"));

    QPixmap buttonPlay("C:/Users/mylle/Documents/AppMusic/resources/play.png");
    ui->pushButton_play_pause->setIcon(buttonPlay);

    QPixmap buttonPrevious("C:/Users/mylle/Documents/AppMusic/resources/arrow - previous.png");
    ui->pushButton_previous_music->setIcon(buttonPrevious);

    QPixmap buttonNext("C:/Users/mylle/Documents/AppMusic/resources/arrow.png");
    ui->pushButton_next_music->setIcon(buttonNext);

    QPixmap buttonSearch("C:/Users/mylle/Documents/AppMusic/resources/loupe.png");
    ui->pushButton_search_music->setIcon(buttonSearch);

    QPixmap imageDisc("C:/Users/mylle/Documents/AppMusic/resources/music.png");
    ui->label_image_disc->setPixmap(imageDisc);

    //prepare the connection with spotify API
    this->spotify_connection = new socketConnection();

    this->userThread = new UserRequest(this);
    this->searchThread = new SearchRequest();
    this->playerThread = new PlayerRequest();

    //connect signals to update UI
    //on ok autentication get user_name
    QObject::connect(spotify_connection, &socketConnection::onGetUser, this, &MainWindow::onRequestUserName);

    //on get user name sucess updtae UI
    QObject::connect(userThread, &UserRequest::updateUser, this, &MainWindow::onUserNameUpdate);

    //on search result update UI
    QObject::connect(searchThread, &SearchRequest::updateSearch, this, &MainWindow::onSearchUpdate);

    //on request Track
    connect(ui->listWidget_search_result, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onClickItemSearch(QListWidgetItem*)));

    //on display album image
    QObject::connect(playerThread, &PlayerRequest::updateImage, this, &MainWindow::onImageUpdate);

    //on get audio
    QObject::connect(playerThread, &PlayerRequest::updateAudio, this, &MainWindow::onAudioUpdate);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRequestUserName()
{
    //get user name
    this->userThread->getUserName(this->spotify_connection);
}


void MainWindow::onUserNameUpdate(QString userName)
{
    ui->label_user_name->setText(userName);

}

void MainWindow::onSearchUpdate(QList<Track> *result_list)
{
    this->player->setList_search(*result_list);
    ui->listWidget_search_result->clear();
    ui->listWidget_search_result->setSpacing(3);

    for(int i=0; i< result_list->size(); i++){
        QListWidgetItem *item = new QListWidgetItem(QString::number(i+1) + "-" +
                                                    result_list->at(i).getName()
                                                    + "\n"
                                                    + result_list->at(i).getArtist(),
                                                    ui->listWidget_search_result);
        item->setBackground(QColor(70, 77, 167));
    }

}

void MainWindow::onClickItemSearch(QListWidgetItem *item)
{
    //set new list of payer
    this->player->setList_player(this->player->getList_search());

    //set the current track
    int index = item->text().split("-").at(0).toInt();
    this->player->setCurrentTrack(index-1);

    //set name of choosed music
    ui->label_artist_name->setText(this->player->getCurrentTrack().getArtist());
    ui->label_music_name->setText(this->player->getCurrentTrack().getName());

    //get the image of music
    QUrl url = this->player->getCurrentTrack().getImage_url();
    this->playerThread->getImage(this->spotify_connection,url);

    //get the audio of music
    QString track_id = this->player->getCurrentTrack().getId_track();
    this->playerThread->getAudio(this->spotify_connection, track_id);
}


void MainWindow::on_pushButton_grant_clicked()
{
    this->spotify_connection->grant();
}


void MainWindow::on_pushButton_search_music_clicked()
{
    if(ui->line_search_music->text().isEmpty())
        return;

    QString search_text = ui->line_search_music->text();
    this->searchThread->searchMusic(spotify_connection, search_text);
}

void MainWindow::onImageUpdate(QImage *image)
{
    ui->label_image_disc->setPixmap(QPixmap::fromImage(*image));
}

void MainWindow::on_pushButton_next_music_clicked()
{
    if(this->player->hasNextTrack())
    {
        ui->pushButton_next_music->setEnabled(true);
        ui->pushButton_previous_music->setEnabled(true);
        setTrack(this->player->nextTrack());
    }
    else {
        ui->pushButton_next_music->setEnabled(false);
    }
}

void MainWindow::onAudioUpdate(QByteArray data)
{
    QBuffer *buffer = new QBuffer(this->audio);
    buffer->setData(data);
    if(!buffer->open(QIODevice::ReadOnly))
        qDebug() << "Buffer not opened";

    buffer->seek(qint64(0));
    this->audio->setAudioOutput(this->audioOutput);
    this->audioOutput->setVolume(10);
    this->audio->setSourceDevice(buffer, QUrl("foo.mp3"));

    //this->audio->play();
    qDebug() << "Play audio";


    QObject::connect(this->audio, &QMediaPlayer::mediaStatusChanged,
                     [=](QMediaPlayer::MediaStatus status)
    { qDebug() << "MediaStatus:" << this->audio->mediaStatus() << "|" << status; });

    QObject::connect(this->audio, &QMediaPlayer::errorOccurred,
                     [=](QMediaPlayer::Error error)
    { qDebug() << "Error:" << this->audio->errorString() << "|" << error; });

    QObject::connect(this->audio, &QMediaPlayer::playbackStateChanged,
                     [=](QMediaPlayer::PlaybackState state)
    { qDebug() << "PlaybackState:" << this->audio->playbackState() << "|" << state; });

    this->audio->play();
    qDebug() << "MediaStatus:" << this->audio->mediaStatus(); // MediaStatus: QMediaPlayer::NoMedia


}

void MainWindow::on_pushButton_previous_music_clicked()
{
    if(this->player->hasPreviousTrack())
    {
        ui->pushButton_previous_music->setEnabled(true);
        ui->pushButton_next_music->setEnabled(true);
        setTrack(this->player->previousTrack());
    }
    else{
        ui->pushButton_previous_music->setEnabled(false);
    }
}

void MainWindow::setTrack(Track * track)
{
    ui->label_artist_name->setText(track->getArtist());
    ui->label_music_name->setText(track->getName());
    this->playerThread->getImage(this->spotify_connection, track->getImage_url());
    this->playerThread->getAudio(this->spotify_connection, track->getId_track());

}


void MainWindow::on_line_search_music_editingFinished()
{
    if(ui->line_search_music->text().isEmpty())
        return;

    QString search_text = ui->line_search_music->text();
    this->searchThread->searchMusic(spotify_connection, search_text);
}

