#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Client nhập số từ bàn phím và gửi sang server

int main(int argc, char* argv[])
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(server_ip);
    addr.sin_port = htons(server_port);

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }

    // Nhan tin nhan tu server
    char buf[256];
    int len = recv(client, buf, sizeof(buf), 0);
    buf[len] = 0;
    printf("%s\n", buf);
    
    printf("Data send to server:\n");
    while (1)
    {
        char data[256];
        //scanf("%[^\n]s", data);
        fgets(data, 256, stdin);
        //printf("%d", strlen(data));

        // Gui mang sang server
        send(client, data, strlen(data), 0);
    }

    
    
    close(client);
}
