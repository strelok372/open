#include "pch.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "winsock2.h"
#include "ws2tcpip.h"
#include <time.h>
#include <conio.h>
#include <vector>
#include <string>
#define MY_PORT "4390"
#pragma comment (lib, "ws2_32.lib")


void delay(int ms) {
	int a = clock() + ms;
	while (clock() < a);
}

class user {
	std::string login = "";
	std::string password = "";
	int permissions = 0;
public:
	user() {};
	user(std::string l, std::string p, int e) : login(l), password(p), permissions(e) {};
	const char* getlogin() { return login.c_str(); }
	const char* getpassword() { return password.c_str(); }
};

static user us[10];

int finduser(char* login) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(login, us[i].getlogin()))
			return i;
	}
	return -1;
}

bool login(int accept_socket) { //процедура логирования
	char l[64]; //буфер сообщения
	int count = 5; //попытки
	int number;
	while (true) {
		if (count > 0) {
			int bytes = recv(accept_socket, l, sizeof(l), 0);
			if (l[0] == 0) return false;
			char* lg = new char[bytes];
			for (int i = 0; i < bytes; i++) {
				lg[i] = l[i];
			}
			if ((number = finduser(lg)) >= 0) {
				delete[] lg;
				send(accept_socket, "1", 1, 0);
				bytes = recv(accept_socket, l, sizeof(l), 0);
				if (l[0] == 0) return false;
				lg = new char[bytes];
				if (strcmp(lg, us[number].getpassword())) return true;
			}
			else count--;
			delete[] lg;
		}
		else {
			//char msg[] = "Too many attemps, try again after 15 minutes";
			send(accept_socket, "-1", 1, 0);
			//send(accept_socket, msg, sizeof(msg), 0);
			//shutdown(accept_socket);
			delay(9000000);
			count = 5;
		}
	}
}


//серверу для записи событий
char getlog() {
	time_t cl;
	time(&cl);
	return *ctime(&cl);
	//std::cout << ctime(&cl) << ": " << msg << "\n";
	//return os;
}

int main()
{
	sockaddr_in *clsin = new sockaddr_in;
	user u = { "admin", "pass1234", 2 };
	us[0] = u;
	setlocale(LC_ALL, "Russian");
	sockaddr_storage stor_addr;
	socklen_t addr_size;
	addrinfo addr, *res;
	int s, buflen, bytes, acceptsocket;; //сокет основной  //новое соединение должно записываться в отдельный дескриптор сокета, потому что предыдущий по-прежнему ожидает соединения
	int status; //обработка ошибок, функции возвращают -1 если что-то идёт не так

	WSAData wsstruct;
	if ((status = WSAStartup((2, 2), &wsstruct)) != 0)
	{
		std::cout << "Невозможно инициализировать структуру WSA\n";
		WSACleanup();
	};

	memset(clsin, 0, sizeof(clsin));
	memset(&addr, 0, sizeof(addr)); //очистка addr
	addr.ai_family = AF_UNSPEC; //автоматический выбор между IPv4 и IPv6
	addr.ai_socktype = SOCK_STREAM; //выбран потоковый, а не пакетный способ
	addr.ai_flags = AI_PASSIVE; //заполняется, если необходимо использовать свой IP адрес
	status = getaddrinfo(NULL, MY_PORT, &addr, &res);
	s = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //инициализация сокета из структуры res
	addr_size = sizeof(stor_addr);
	status = bind(s, res->ai_addr, res->ai_addrlen); //привязка к порту для последующего прослушивания, может использоваться и для клиента, но функция connect обычно сама подбирает локальный порт
	status = listen(s, 5); //ожидание входящего подключение для последующей обработки, принимает сокет и кол-во разрешённых входных подключений в очереди

	acceptsocket = accept(s, (struct sockaddr *)&stor_addr, &addr_size);

	status = getpeername(acceptsocket, (sockaddr*)clsin, (int*)sizeof(&clsin));
	char ip4[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clsin->sin_addr, ip4, INET_ADDRSTRLEN);
	std::cout << getlog() << "Client connected from: " << ip4;

	//char buf[256];
	//const char* msg = "Hello, my friend";
	//while (true) {
	//	bytes = send(acceptsocket, msg, strlen(msg), 0); //вернёт кол-во байтов которые удалось отправить
	//	buflen = recv(acceptsocket, buf, sizeof(buf), 0);
	//	if (buflen == 0)
	//		break;
	//}


	delete clsin;
	closesocket(acceptsocket);
	freeaddrinfo(res);
	closesocket(s);
	WSACleanup();
	return 0;
}
//
//int getror() {
//	freeaddrinfo(res);
//	WSACleanup();
//	return 1;
//}