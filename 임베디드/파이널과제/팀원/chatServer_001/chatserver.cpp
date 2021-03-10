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

        if (line.compare(QString("#game1")))
		{
			gameBaseball();
        }


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


void chatServer::gameBaseball()
{
	int computerBall[3]; // 컴퓨터의 볼을 저장할 int형 배열
	int i, j; // 반복을 위한 변수
	int temp; // 난수 중복 체크를 위한 변수
	int userBall[3]; // 사용자의 볼을 저장할 int형 배열
	int count = 1; // 회차를 확인할 변수 9회까지 가능
	int strike; // 스트라이크의 수를 세기 위한 변수
	int ball; // 볼의 수를 세기 위한 변수

	srand((unsigned)time(NULL));
	for (i = 0; i < 3; i++)
	{
		temp = (rand() % 9) + 1; // temp변수에 현재 랜덤 값을 저장
		computerBall[i] = temp; // temp값을 컴퓨터의 볼에 저장
		for (j = 0; j < i; j++) // 현재 추가된 만큼 반복하며
			if (temp == computerBall[j] && i != j) // 만약 현재 temp값과 이전에 넣은 값 중 동일한 게 있다면
				i--; // i의 값을 줄여 다시 이전으로 돌아가도록
	}

	QTcpSocket* client = (QTcpSocket*)sender();

	int buf1 = 0;

	while (1)
	{
		client->write(QString("[%d회차 숫자야구]\n").arg(count).toUtf8());
		client->write(QString("1부터 9까지 중복되지 않는 세 숫자를 입력하세요").toUtf8());
		QString answer = QString::fromUtf8(client->readLine());

		buf1 = answer.toInt();
		userBall[0] = buf1 / 100;
		userBall[1] = (buf1 % 100) / 10;
		userBall[2] = buf1 % 10;

		ball = 0;
		strike = 0;

		for (i = 0; i < 3; i++) // computerBall 1~3번째에 따라 각 userBall 1~3번째를 확인하기 위한 반복
			for (j = 0; j < 3; j++)
				if (computerBall[i] == userBall[j]) // computerBall과 userBall의 값이 같다면
					if (i == j) // 같은 위치일 경우
						strike++; // 스트라이크 개수 증가
					else // 다른 위치일 경우
						ball++; // 볼 개수 증가

		// 확인한 결과를 출력
		client->write(QString("[결과]스트라이크 : %d, 볼 : %d\n\n").arg(strike).arg(ball).toUtf8());

		if (strike == 3) // 만약 스트라이크 개수가 3개이면 승리
		{

			client->write("***** 승리했습니다. *****\n\n");;
			break;
		}
		else if (count == 9) // 만약 9회차인데도 승리하지 못하면 패배
		{
			client->write(QString("***** 패배했습니다.. 정답 : %d %d %d *****\n\n").arg(computerBall[0]).arg(computerBall[1]).arg(computerBall[2]).toUtf8());

			break;
		}
		count++;
	}


}
