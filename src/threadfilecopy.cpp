#include "threadfilecopy.h"
#include "audiofile.h"

#include <QThread>
#include <QDebug>
#include <QDir>

ThreadFileCopy::ThreadFileCopy()
{

}

ThreadFileCopy::~ThreadFileCopy()
{

}

void ThreadFileCopy::setFileList(QList<QVariant> files)
{
    fileList = files;
}


void ThreadFileCopy::addFile(QString fileName)
{
    QDir collectionDir = QDir();
    QString collectionDirString = QString(QDir::homePath()+"/.radon/collection/");
    AudioFile *audioFile = new AudioFile(fileName);
    QFile file;
    if(audioFile->artist.length() == 0 || audioFile->title.length() == 0)
    {
        if(audioFile->artist.length() == 0)
        {
            audioFile->artist = QString("Unknow Artist");
        }

        if(audioFile->title.length() == 0)
        {
            audioFile->title = QString("Unknow Track");
        }
        audioFile->sync();
    }
    collectionDir.mkpath(collectionDirString+QString("/"+audioFile->artist.toUtf8()));
    file.copy(fileName,collectionDirString+"/"+audioFile->artist.toUtf8()+"/"+audioFile->title.toUtf8()+".mp3");
    emit fileCopied(fileName);
}

void ThreadFileCopy::proccess()
{
    qDebug() << "process";
    for(int i=0; i<fileList.length(); i++)
    {
        addFile(fileList[i].toString());
    }
}

void ThreadFileCopy::stop()
{

}
