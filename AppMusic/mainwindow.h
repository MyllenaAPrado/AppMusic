#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <socketconnection.h>
#include <userrequest.h>
#include <searchrequest.h>
#include <playerrequest.h>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <player.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    socketConnection *spotify_connection;
    UserRequest *userThread;
    PlayerRequest *playerThread;
    SearchRequest *searchThread;
    QVBoxLayout *layout = new QVBoxLayout();
    Player *player = new Player();
    QMediaPlayer *audio;
    QAudioOutput *audioOutput;

    void setTrack(Track * track);

public slots:
    void onUserNameUpdate(QString userName);
    void onSearchUpdate(QList<Track> *result_list);
    void onRequestUserName();
    void onClickItemSearch(QListWidgetItem *item);
    void onImageUpdate(QImage *image);
    void onAudioUpdate(QByteArray data);

private slots:
    void on_pushButton_grant_clicked();
    void on_pushButton_search_music_clicked();
    void on_pushButton_next_music_clicked();
    void on_pushButton_previous_music_clicked();
    void on_line_search_music_editingFinished();
};
#endif // MAINWINDOW_H
