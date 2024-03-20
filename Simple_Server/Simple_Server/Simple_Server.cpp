#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <chrono>
#include <thread>

#pragma comment(lib,"ws2_32.lib")

int main()
{

    WSADATA ds;

    if (WSAStartup(MAKEWORD(2, 2), &ds))
    {
        std::cout << "[-] Failed to Initialize WinSOCK API [-]" << '\n';
    }
    std::cout << "[+] WinSOCK Initialized [+]" << '\n';

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "[+] Setting Up Socket [+]" << '\n';

    SOCKET listeningSocket;
    SOCKET newConnection;

    listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    int PORT = 9003;

    int clientAddr_size = sizeof(clientAddr);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listeningSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cout << "[-] Failed to Bound the socket [-]" << '\n';
        closesocket(listeningSocket);
        WSACleanup();

        return -1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "[+] Socket Bounded Successfully [+]" << '\n';

    if (listen(listeningSocket, 5) == SOCKET_ERROR)
    {
        std::cout << "[-] Failed to setup for listen() state [-]" << '\n';
        closesocket(listeningSocket);
        WSACleanup();

        return -1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "[+] Listening......[+]" << '\n';

    newConnection = accept(listeningSocket, (sockaddr*)&clientAddr, &clientAddr_size);

    std::cout << "[+] New Connection Established [+]" << '\n';

    char ipBuffer[50];

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "[+] Client IP : " << inet_ntop(AF_INET, &(clientAddr.sin_addr.s_addr), ipBuffer, 50) << '\n';
    std::cout << "[+] Client IP Size : " << sizeof(inet_ntop(AF_INET, &(clientAddr.sin_addr.s_addr), ipBuffer, 50)) << " Bytes" << '\n';
    std::cout << "[+] Client Port : " << clientAddr.sin_port << '\n';
    std::cout << '\n';

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "[+] Closing all the sockets [+]" << '\n';
    closesocket(listeningSocket);
    closesocket(newConnection);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "[+] Cleaning up [+]" << '\n';
    WSACleanup();

    return 0;
}
