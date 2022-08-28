#ifndef EVENTSERVER_H
#define EVENTSERVER_H

#include <QObject>

class EventServer : public QObject
{
    Q_OBJECT
public:
    explicit EventServer(QObject *parent = nullptr);

signals:

};

#endif // EVENTSERVER_H
