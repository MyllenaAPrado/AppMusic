#include "itemsearchresult.h"
#include "ui_itemsearchresult.h"

ItemSearchResult::ItemSearchResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemSearchResult)
{
    ui->setupUi(this);
}

ItemSearchResult::~ItemSearchResult()
{
    delete ui;
}

void ItemSearchResult::setMusicName(QString name)
{
    ui->label_music_name->setText(name);
}

void ItemSearchResult::setArtistName(QString name)
{
    ui->label_artist_name->setText(name);
}
