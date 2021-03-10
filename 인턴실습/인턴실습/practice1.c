#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

void error_handling(char* message);

int main()
{
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;

    short port = 5001;
    int szClntAddr;
    char message[] = "Hello World!";

    //���� �ʱ�ȭ, ���� ����ϱ� �� �ʱ�ȭ �ؾ���. 
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        error_handling(" WSAStartup() error!");
    }
    // TCP ���ϻ���
    hServSock = socket(PF_INET, SOCK_STREAM, 0);

    if (hServSock == INVALID_SOCKET)
    {
        error_handling("socket() error!");
    }

    //������ �ּ� ����
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //���� pc  ip�ּ� ���
    servAddr.sin_port = htons(port); //��Ʈ��ȣ

    //�ּ� ����
    if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    {
        error_handling("bind() error!");
    }

    //���� ������ �ְ�
    if (listen(hServSock, 5) == SOCKET_ERROR)
    {
        error_handling("listen() error!");
    }

    //���� ����
    szClntAddr = sizeof(clntAddr);
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);

    if (hClntSock == INVALID_SOCKET)
    {
        error_handling("accept() error!");
    }

    send(hClntSock, message, sizeof(message), 0);

    closesocket(hClntSock);
    closesocket(hServSock);
    WSACleanup();

    return 0;

}


void error_handling(char* message)
{
    fputs(message, stderr);
    fputc("\n", stderr);
    exit(1);
}