#include "chatserver.h"
#include <QTcpSocket>
#include <QRegExp>
#include <QTextCodec>
#include <QString>

chatServer::chatServer(QObject* parent) : QTcpServer(parent)
{
    userAmount=-1;
}

void chatServer::incomingConnection(int socketfd)
{
    QTcpSocket* client=new QTcpSocket(this); //클라리언트 소켓 새성
    client->setSocketDescriptor(socketfd); //소켓드스크립터 설정
    clients.insert(client); //클라이언트 집합에 새로 들어온 클라이언트 추가


    printf("New Client from:%s\n",client->peerAddress().toString().toLocal8Bit().data());

    connect(client,SIGNAL(readyRead()),this,SLOT(readyRead()));

    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
}

void chatServer::readyRead()
{
    QTcpSocket* client=(QTcpSocket*)sender(); //메시지가 들어온 클라이언트를 감지하는 함수 sender
    while(client->canReadLine())
    {
        QString line=QString::fromUtf8(client->readLine());
        printf("Read Line:%s\n",line.toLocal8Bit().data());

        QRegExp meRegex("^/me:(.*)$");

        if(meRegex.indexIn(line)!=-1) //새로 들어온 유저면
        {
            QString user=QString("user%1").arg(++userAmount);
            users.insert(client,user);
            foreach(QTcpSocket* client,clients)
            {
                QString temp=QString("server:%1 is connneted\n").arg(user);
                client->write(temp.toUtf8());
                sendUserList();
            }

        }
        else if(users.contains(client)) //이미 있는 유저가 메시지를 보낸경우
        {
            QString message=line;
            QString user=users[client];
            printf("User:%s\n",user.toLocal8Bit().data());
            printf("Message:%s\n",message.toLocal8Bit().data());

            foreach(QTcpSocket* otherClient,clients)
                otherClient->write(QString("%2:%1").arg(message).arg(users[client]).toUtf8());
        }
        else
        {
            qWarning()<<"Got bad message from client:"<<client->peerAddress().toString()<<line;
        }
    }
}

void chatServer::disconnected()
{
    QTcpSocket* client=(QTcpSocket*)sender();
    printf("Client disconnected:%s\n",client->peerAddress().toString().toLocal8Bit().data());

    clients.remove(client);

    QString user=users[client];
    users.remove(client);

    sendUserList();
    foreach(QTcpSocket* client,clients)
    {
        client->write(QString("server:"+user+"exit the server.\n").toUtf8());
    }

}


void chatServer::sendUserList()
{
    QStringList userList;
    foreach(QString user,users.values())
        userList<<user;

    foreach(QTcpSocket* client,clients)
        client->write(QString("users:"+ userList.join(",")+"\n").toUtf8());
}
