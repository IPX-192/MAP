#include "CDataParseThread.h"

CDataParseThread::CDataParseThread()
{

}

CDataParseThread::~CDataParseThread()
{
    if(this->isRunning())
    {
        setStopFlag(true);
        this->wait();
    }
}

void CDataParseThread::setStopFlag(bool bflag)
{
    m_bStopRead = bflag;
}

void CDataParseThread::run()
{

}
