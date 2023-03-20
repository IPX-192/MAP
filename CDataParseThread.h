#ifndef CDATAPARSETHREAD_H
#define CDATAPARSETHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QQueue>
#include <QDebug>
#include <QVariant>
class CDataParseThread : public QThread
{
    Q_OBJECT
public:
    CDataParseThread();
    ~CDataParseThread();


    void setStopFlag(bool bflag);

protected:
    void run();

private:
    volatile bool  m_bStopRead;
    QMutex         m_Rlock;
};

#endif // CDATAPARSETHREAD_H
