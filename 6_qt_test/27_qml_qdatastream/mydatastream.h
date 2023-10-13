#ifndef MYDATASTREAM_H
#define MYDATASTREAM_H

#include <QObject>

class myDataStream : public QObject
{
    Q_OBJECT
public:
    explicit myDataStream(QObject *parent = nullptr);

    static void myTest();

signals:

};

#endif // MYDATASTREAM_H
