#pragma comment (lib,"Ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <sstream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#define MY_PORT "4390"
using std::cerr;
char ip[15] = { "10.0.0.1" };
int port;
addrinfo *res = new addrinfo;

bool login(int s, const char text[]) {
	char l[64] = "\0";
	while (1) {
		std::cout << text;
		std::cin >> l;

		int bytes = send(s, l, sizeof(l), 0);
		bytes = recv(s, l, sizeof(l), 0);
		if (l[0] == (1)) {
			break;
		}
		if (l[0] == (-1)) {
			return false;
		}

	}
	return true;
}

void getinfo(int a) {
	switch (a) {
	case (1):
		std::cout << "Соединение установлено!\n";
		break;
	case (2):
		std::cout << "Неверный логин!\n";
		break;
	case (3):
		std::cout << "Неверный пароль!\n";
		break;
	case (4):
		std::cout << "Вы успешно вошли в систему!\n";
		break;
	case (5):
		std::cout << "Слишком много попыток, попробуйте ещё раз через 15 минут!\n";
		break;
	}
}

int connectionmenu(addrinfo *addr) {
	int s, status;
	int sw = 0;
	while (true) {
		system("cls");
		std::cout << "***Connection menu***\n\n";
		switch (sw) {
		case(0):
			std::cout << ">Login\nChange IP\nChange port\nExit";
			break;
		case(1):
			std::cout << "Login\n>Change IP\nChange port\nExit";
			break;
		case(2):
			std::cout << "Login\nChange IP\n>Change port\nExit";
			break;
		case(3):
			std::cout << "Login\nChange IP\nChange port\n>Exit";
			break;
		}
		std::cout << "\n\nCurrent IP: " << ip << "\n";
		std::cout << "Current port: " << port;

		switch (_getch()) {
		case(72):
			if (sw > 0) sw--;
			break;
		case(80):
			if (sw < 3) sw++;
			break;
		case(13):
			switch (sw) {
			case(0):	
				status = getaddrinfo(ip, (char*)port, addr, &res);
				s = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //инициализация сокета из структуры res
				status = connect(s, res->ai_addr, res->ai_addrlen); //(КЛИЕНТ)присоединение к удалённому адресу, также вызывает bind для подбора локального порта		
				if (status != (-1)) {
					std::cout << "You have been connected!";
					if (login(s, "Login: "))
						if (login(s, "Password: "))
							return 1;
				}
				break;
			case(1):
			{
				//std::string p;
				//char *p = new char;
				char p[15];
				system("cls");
				std::cout << "Input IP in format x.x.x.x\n";
				std::cin >> std::setw(14) >> p;				
				//std::strcpy(ip, &p);	
				strcpy_s(ip, 14, p);
				inet_pton(AF_INET, p, &(addr->ai_addr));
				//p = NULL;
				//delete[] p;
				std::cin.ignore(32767, '\n');
				break;
			}
			case(2):
				exit(1);
				break;
				break;
			case(3):
				exit(1);
				break;
				break;
			}
		}
	}
}


int main()
{

	WSADATA wsaData;
	int status, s; //обработка ошибок, функции возвращают -1 если что-то идёт не так и сокет
	status = WSAStartup(MAKEWORD(2, 2), &wsaData);
	setlocale(LC_ALL, "Russian");
	addrinfo addr;

	WSAData wsstruct;
	if ((status = WSAStartup((2, 2), &wsstruct)) != 0)
	{
		std::cout << "Невозможно инициализировать структуру WSA\n";
		WSACleanup();
	};

	memset(&addr, 0, sizeof(addr)); //очистка addr
	addr.ai_family = AF_UNSPEC; //автоматический выбор между IPv4 и IPv6
	addr.ai_socktype = SOCK_STREAM; //выбран потоковый, а не пакетный способ
	s = connectionmenu(&addr);

	//s = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //инициализация сокета из структуры res
	//status = connect(s, res->ai_addr, res->ai_addrlen); //(КЛИЕНТ)присоединение к удалённому адресу, также вызывает bind для подбора локального порта		
	//if (status != (-1)) {
	//	std::cout << "You have been connected!";
	//	if (login(s, "Login: "))
	//		if (login(s, "Password: "))
	//			return 1;
	//}
	/*char buf[256];
	int buflen = recv(s, buf, sizeof(buf), 0);
	for (int i = 0; i < buflen; i++) {
		std::cout << buf[i];
	}*/
	
	freeaddrinfo(res);
	closesocket(s);
	WSACleanup();
	return 0;
}