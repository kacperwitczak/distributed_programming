#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// prosty moduł klienta
// komunikacji za pomocą Winsock
// użycie: klient.exe -s:IP
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_COUNT 5
#define DEFAULT_PORT 5000
#define DEFAULT_BUFFER 4096
#define DEFAULT_MESSAGE "Wiadomość testowa, Systemy Operacyjne 2002"
// tylko Visual C++
#pragma comment(lib, "ws2_32.lib")
char szServer[128], szMessage[1024];
// funkcja sposob_uzycia
void sposob_uzycia()
{
	printf("Klient.exe -s:IP\n");
	ExitProcess(1);
}
void WalidacjaLiniiPolecen(int argc, char** argv)
{
	int i;
	if (argc < 2)
	{
		sposob_uzycia();
	}
	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (tolower(argv[i][1]))
			{
			case 's':
				if (strlen(argv[i]) > 3)
					strcpy(szServer, &argv[i][3]);
				break;
			default:
				sposob_uzycia();
				break;
			}
		}
	}
}
int main(int argc, char* argv[])
{
	WSADATA wsd;
	SOCKET sClient;
	char szBuffer[DEFAULT_BUFFER];
	int ret, i;
	struct sockaddr_in server;
	struct hostent* host = NULL;
	// linia poleceń
	WalidacjaLiniiPolecen(argc, argv);
	// inicjuj Winsock 2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("Błąd ładowania Winsock 2.2!\n");
		return 1;
	}
	strcpy(szMessage, DEFAULT_MESSAGE);
	// twórz gniazdo do nasłuchu połączeń klientów
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sClient == INVALID_SOCKET)
	{
		printf("Błąd funkcji socket(): %d\n", WSAGetLastError());
		return 1;
	}
	// wybierz interfejs
	server.sin_addr.s_addr = inet_addr(szServer);
	server.sin_family = AF_INET;
	server.sin_port = htons(DEFAULT_PORT);
	// jeśli adres nie był w postaci xxx.yyy.zzz.ttt
	// to spróbuj go wydobyć z postaci słownej
	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(szServer);
		if (host == NULL)
		{
			printf("Nie udało się wydobyć nazwy serwera: %s\n", szServer);
			return 1;
		}
		CopyMemory(&server.sin_addr, host->h_addr_list[0], host->h_length);
	}
	if (connect(sClient, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Błąd funkcji connect(): %d\n", WSAGetLastError());
		return 1;
	}
	// wysyłaj i odbieraj dane
	for (i = 0; i < DEFAULT_COUNT; i++)
	{
		ret = send(sClient, szMessage, strlen(szMessage), 0);
		if (ret == 0)
			break;
		else if (ret == SOCKET_ERROR)
		{
			printf("Błąd funkcji send(): %d\n", WSAGetLastError());
			return 1;
		}
		printf("Wysłano %d bajtów\n", ret);
		ret = recv(sClient, szBuffer, DEFAULT_BUFFER, 0);
		if (ret == 0)
			break;
		else if (ret == SOCKET_ERROR)
		{
			printf("Błąd funkcji recv(): %d\n", WSAGetLastError());
			return 1;
		}
		szBuffer[ret] = '\0';
		printf("RECV [%d bajtów]: '%s'\n", ret, szBuffer);
	}
	closesocket(sClient);
	WSACleanup();
	return 0;
}
