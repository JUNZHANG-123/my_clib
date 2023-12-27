#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QList>
#include <QEventLoop>
#include <QFileInfo>
#include <QSslError>
#include <QFile>

#include <stdio.h>


class DownloadManager : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *m_manager;

public:
    explicit DownloadManager(QObject *parent = nullptr);

    void resetManager();
    void startDownload();

public slots:
    void onRequestFinished(QNetworkReply*);
    void onReadyRead();
    void onAsynDownloadProgressChanged(qint64 bytesReceived, qint64 bytesTotal);

signals:
//    void finished(QNetworkReply*);
//    void downloadProgress();
//    void readyRead();
};

#endif // DOWNLOADMANAGER_H
