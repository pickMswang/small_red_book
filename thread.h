#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QDebug>
#include "TCPNet.h"
#include "TCPKernel.h"

class TCPNet;
class IKernel;

class RecvThread:public QThread
{
    Q_OBJECT
public:
    TCPNet* tcpNet;
public:
    RecvThread(TCPNet*);
    void run();
};

#endif // THREAD_H

