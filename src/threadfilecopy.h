#ifndef THREADFILECOPY_H
#define THREADFILECOPY_H

#include <QObject>

class ThreadFileCopy : public QObject
{
    Q_OBJECT
public:
    ThreadFileCopy();
    ~ThreadFileCopy();

    void setFileList(QList<QVariant> files);
    void addFile(QString fileName);

private:
    QList<QVariant> fileList;
    QThread* thread;

public slots:
    void proccess();
    void stop();
    void rescanCollection();

signals:
    void finishCopy();
    void fileCopied(QString fileName);
};

#endif // THREADFILECOPY_H
