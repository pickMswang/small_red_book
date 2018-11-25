#include "thread.h"

RecvThread::RecvThread(TCPNet* pNet)
{
    tcpNet = pNet;
}

void RecvThread::run()
{
    char pszbuf[2048];
    int ret;
    while(1)
    {

        //接收包大小
        ret = recv(tcpNet->m_sockClient,pszbuf,sizeof(pszbuf),0);
        if(ret < 0)
          //  qDebug()<<"recv failed"<<endl;

        /*while(nPackSize)
        {
           nRelReadNum =  recv(tcpNet->m_sockClient,pszbuf+noffset,nPackSize,0);
           noffset += nRelReadNum;
           nPackSize -= nRelReadNum;

         }*/

        //交给核心处理类处理
        tcpNet->m_pKernel->DealData(pszbuf);

    }
}
