#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

const char* host = "127.0.0.1";
int port = 7000;

int main() {
    // code about winodws socket is borrowed from
    // https://shengyu7697.github.io/cpp-windows-tcp-socket/
    SOCKET sock;
    struct sockaddr_in serv_name {};
    int status;
    char indata[1024] = {0}, outdata[1024] = {0};

    // init winsock
    WSADATA wsa = { 0 };
    WORD wVer = MAKEWORD(2, 2);
    WSAStartup(wVer, &wsa);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != NO_ERROR) {
        printf("Error: init winsock\n");
        exit(1);
    }

    // create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation error");
        exit(1);
    }

    // server address
    serv_name.sin_family = AF_INET;
    inet_pton(AF_INET, host, &serv_name.sin_addr);
    serv_name.sin_port = htons(port);

    status = connect(sock, (struct sockaddr *)&serv_name, sizeof(serv_name));
    if (status == -1) {
        perror("Connection error");
        exit(1);
    }

    while (1) {
        printf("Press button (0: up, 1: down, 2: floor 1, 3: floor 2): ");
        std::cin.getline(outdata, sizeof(outdata));
        //printf("send: %s\n", outdata);
        send(sock, outdata, strlen(outdata), 0);

        int nbytes = recv(sock, indata, sizeof(indata), 0);
        if (nbytes <= 0) {
            closesocket(sock);
            printf("server closed connection.\n");
            break;
        }
        //printf("recv: %s\n", indata);
    }
    WSACleanup();

    return 0;
}
