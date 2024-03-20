#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

#pragma comment(lib , "ws2_32.lib")

int main(int argc, char* argv[])
{

	if (argc < 2)
	{
		std::cout << "\n[+] Usage : Client.exe ip_address port_number [+]" << '\n';
		std::cout << '\n';

		return 0;
	}

	//server Port Number
	int port = std::atoi(argv[2]);

	//server IP Address
	long IP_Addr;

	//Converting string representaion of IP to it's binary form
	inet_pton(AF_INET, argv[1], &IP_Addr);

	WSADATA ds;

	if (WSAStartup(MAKEWORD(2, 2), &ds))
	{
		std::cout << "[-] Failed to intialize WinSOCK API [-]" << '\n';
		std::cout << "[-] Error Code : " << WSAGetLastError() << '\n';

		return -1;
	}

	std::cout << "[+] WinSOCK initialized successfully [+]" << '\n';

	Sleep(30);

	std::cout << "[+] Creating Socket [+]" << '\n';

	Sleep(30);

	SOCKET clientSocket;

	if ((clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		std::cout << "[-] Unable to Create Socket [-]" << '\n';
		std::cout << "[-] Error Code : " << WSAGetLastError() << '\n';
		WSACleanup();

		return -1;
	}
	std::cout << "[+] Socket Created [+]" << '\n';


	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = IP_Addr;


	std::cout << "[+] Connecting ......." << '\n';

	if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		std::cout << "[-] Failed to connect to server [-]" << '\n';
		std::cout << "[-] Error Code : " << WSAGetLastError() << '\n';

		if (WSAGetLastError() == WSAECONNREFUSED)
		{
			std::cout << "[-] Connection refused by the server. Make sure the server is running and listening." << '\n';
		}

		closesocket(clientSocket);
		WSACleanup();

		return -1;
	}
	std::cout << "[+] Connected........" << '\n';

	Sleep(50);

	std::cout << "[+] Cleaning Up .........." << '\n';
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}