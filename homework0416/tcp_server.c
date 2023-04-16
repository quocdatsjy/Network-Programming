#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);
    char* fileName1 = argv[2];
    char* fileName2 = argv[3];
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listener == -1) {
        perror("socket() failed");
        return 1;
    }
    printf("Created listener");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(addr);

    int client = accept(listener, (struct sockaddr *)&clientAddr, (socklen_t*) &clientAddrLen);
    printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    FILE *f1 = fopen(fileName1, "rb");
    char buf[256];
    fgets(buf, 256, f1);
    send(client, buf, strlen(buf), 0);
    fclose(f1);

    char arr[256];
    int size = sizeof(arr);
    FILE *f = fopen(fileName2, "wb");
    while (1)
    {
        int ret = recv(client, arr, size, 0);
        if (ret <= 0)
            break;
        if (ret < sizeof(arr)) arr[ret] = 0;
        //puts(arr);
        fprintf(f, "%s",arr);
    }

    fclose(f);

    close(client);
    close(listener);
    return 0;

}