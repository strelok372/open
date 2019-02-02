#include "pch.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "winsock2.h"
#include "ws2tcpip.h"

#pragma comment (lib, "ws2_32.lib")

int main()
{
	setlocale(LC_ALL, "Russian");
	int result;

	WSAData wsstruct;
		if ((result = WSAStartup((2,2), &wsstruct)) != 0) 
			{
				std::cout << "Невозможно инициализировать структуру WSA\n";
				WSACleanup();
			}

	SOCKET sock;
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
			{
				std::cout << "Не получилось создать сокет\n";
				WSACleanup();
			}
	
	sockaddr_in soain;
	soain.sin_family = 2;
	soain.sin_port = htons(8000);
	soain.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//soain.sin_addr.S_un.S_addr = inet_pton(2, "127.0.0.1", &soain.sin_addr);

		if (bind(sock, (SOCKADDR*)&soain, sizeof(soain)) == SOCKET_ERROR)
			{
				std::cout << "Привязка не удалась!\n";
				WSACleanup();
				closesocket(sock);
			}

		if (listen(sock, SOMAXCONN) != 0)
			{
				std::cout << "Не удалось открыть сокет для подключения!\n";
			}

	SOCKET accpt = accept(sock, NULL, NULL);
	char buf[256]="";	
		if (accpt == SOCKET_ERROR)
			{
				closesocket(sock);
				WSACleanup();
			}
		else
			{
				std::cout << "Клиент подключен!\n";
				int bytesrecv = SOCKET_ERROR;
					while (bytesrecv == SOCKET_ERROR)
						{
							char tem[256] = "";
							bytesrecv = recv(accpt, tem, sizeof(tem), 0);						
							if (bytesrecv == 0 || bytesrecv == WSAECONNRESET)
								{
									std::cout << "Клиент разорвал соединение или передача закончена!\n";
									break;
								}
							strcat_s(buf, tem);
						}
				strcat_s(buf, "***ПОЛУЧЕНО***");
				for (char a : buf)
				std::cout << a;
				std::cout << "\n" << "КОНЕЦ ПЕРЕДАЧИ";
				bytesrecv = send(accpt, buf, sizeof(buf), 0);
				shutdown(accpt, 2);
				closesocket(accpt);
			}
	shutdown(sock, 2);
	closesocket(sock);
	WSACleanup();
}
