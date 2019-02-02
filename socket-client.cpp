#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "winsock2.h"
#include "ws2tcpip.h"
#pragma comment (lib, "ws2_32.lib")

int main()
{
	setlocale(LC_ALL, "Russian");
	int result;

	WSAData wsstruct;
	if ((result = WSAStartup((2, 2), &wsstruct)) != 0)
	{
		std::cout << "Невозможно инициализировать структуру WSA";
		WSACleanup();
	}

	SOCKET sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		std::cout << "Не получилось создать сокет";
		WSACleanup();
	}

	sockaddr_in soain;
	soain.sin_family = 2;
	soain.sin_port = htons(8000);
	soain.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//soain.sin_addr.S_un.S_addr = inet_pton(2, "127.0.0.1", &soain.sin_addr);

	if (connect(sock, (SOCKADDR*)&soain, sizeof(soain)) == SOCKET_ERROR)
	{
		std::cout << "Привязка не удалась!";
		WSACleanup();
		return 1;
	}

	int bytessent;
	int bytesrecv = SOCKET_ERROR;
	char *snd = new char[256];
	//char snd[256] = "Client: SENDING MOTHERFCKER";
	char rcv[256] = "";
	std::cout << "Введите слово или строку\n";
	std::cin >> snd;

	bytessent = send(sock, snd, sizeof(snd)+1, 0);
	while (bytesrecv == SOCKET_ERROR)
	{
		bytesrecv = recv(sock, rcv, sizeof(rcv), 0);
		if (bytesrecv == 0 || bytesrecv == WSAECONNRESET)
		{
			std::cout << "Клиент разорвал соединение или передача закончена!\n";
			break;
		}
	}
	for (char a : rcv)
		std::cout << a;

	shutdown(sock, 2);
	closesocket(sock);
	WSACleanup();
}
