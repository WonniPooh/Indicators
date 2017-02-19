#ifndef REPLYHANDLER_H
#define REPLYHANDLER_H

#include <QtNetwork>
#include <QObject>

class ReplyHandler: public QObject
{
    Q_OBJECT

signals:
    void doItAgain();

private:
    QMap<int, QString> prev_data;
    int reply_counter;
public slots:
    void slotHandleReply();

public:
    ReplyHandler(QObject *pobj = 0);
};
#endif // REPLYHANDLER_H
