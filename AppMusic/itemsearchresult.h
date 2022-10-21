#ifndef ITEMSEARCHRESULT_H
#define ITEMSEARCHRESULT_H

#include <QWidget>

namespace Ui {
class ItemSearchResult;
}

class ItemSearchResult : public QWidget
{
    Q_OBJECT

public:
    explicit ItemSearchResult(QWidget *parent = nullptr);
    ~ItemSearchResult();
    void setMusicName(QString name);
    void setArtistName(QString name);

private:
    Ui::ItemSearchResult *ui;
};

#endif // ITEMSEARCHRESULT_H
