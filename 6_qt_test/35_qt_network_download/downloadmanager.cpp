#include "downloadmanager.h"
#include <QDebug>
//这个结构体的用途 看到下面就明白了

typedef struct
{
    QNetworkReply* reply = nullptr;
    QFile* file = nullptr;
}DownloadStorage;
DownloadStorage m_downloadStorage;

DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{
    //1. 实例化 QNetworkAccessManager对象
    m_manager = new QNetworkAccessManager(this);
    //槽函数自己实现
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));

}

void DownloadManager::resetManager()
{
//    //1. 实例化 QNetworkAccessManager对象
//    m_manager = new QNetworkAccessManager(this);
//    //槽函数自己实现
//    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));

}

void DownloadManager::startDownload()
{
    if (m_manager)
    {
        QFile* file = new QFile("./test.exe");
        if (file->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            QNetworkRequest request;
            request.setUrl(QString("https://cdn-file-ssl.ludashi.com/downloader/temp_package/2023-10/%E5%85%89%E5%BD%B1%E9%AD%94%E6%9C%AF%E6%89%8B_4529463453.exe"));

            m_downloadStorage.reply = m_manager->get(request);
            m_downloadStorage.file = file;
            connect(m_downloadStorage.reply, &QNetworkReply::readyRead, this, &DownloadManager::onReadyRead);
            connect(m_downloadStorage.reply, &QNetworkReply::downloadProgress, this, &DownloadManager::onAsynDownloadProgressChanged);
        }
    }
}

void DownloadManager::onReadyRead()
{
    //在这个槽里 找到刚刚保存的file指针 一直写数据
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply && reply == m_downloadStorage.reply)
    {
        m_downloadStorage.file->write(reply->readAll());
        qDebug() << "write";
    }
}

void DownloadManager::onAsynDownloadProgressChanged(qint64 bytesReceived, qint64 bytesTotal)
{
    qint64 kbTotal = bytesTotal / 1024;
    qint64 mbTotal = kbTotal / 1024;

    qint64 kbReceived = bytesReceived / 1024;
    qint64 mbReceived = kbReceived / 1024;

    qDebug() << "kbTotal:" << kbTotal << " mbTotal:" << mbTotal << " kbReceived:" << kbReceived << " mbReceived:" << mbReceived << endl;
}

void DownloadManager::onRequestFinished(QNetworkReply *reply)
{
    if (!reply)
    {
        return;
    }

    if (reply->error() != QNetworkReply::NoError
        || reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
    {
        //error
        reply->deleteLater();
        return;
    }
    //把下载文件的 file close 然后 删除
    if (m_downloadStorage.reply && m_downloadStorage.reply == reply)
    {
        if (m_downloadStorage.file)
        {
            m_downloadStorage.file->close();
            delete m_downloadStorage.file;
            m_downloadStorage.file = nullptr;
        }
    }
    reply->deleteLater();
}

