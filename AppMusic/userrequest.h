#ifndef USERREQUEST_H
#define USERREQUEST_H

#include <QThread>
#include <socketconnection.h>

class UserRequest : public QThread
{
    Q_OBJECT
public:
    explicit UserRequest(QObject *parent =0);
    void getUserName(socketConnection* connection);
    void stop();

signals:
    void updateUser(QString);
};


#endif // USERREQUEST_H
