#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    struct addrinfo *res, *p, hints;
    hints.ai_family = AF_INET;
    int ret = getaddrinfo(argv[1], "http", NULL, &res);
    if(ret == -1) {
        printf("Failed to get IP");
        return 1;
    }
    p = res;
    while(p != NULL) {
        if(p->ai_family == AF_INET) {
            printf("IPv4:%s\n", 
                inet_ntoa(((struct sockaddr_in *)p->ai_addr)->sin_addr));
        } else if (p->ai_family == AF_INET6) {
            char buf[64];
            printf("IPv6:%s\n",
                inet_ntop(AF_INET6, &((struct sockaddr_in6 *)p->ai_addr)->sin6_addr, 
                    buf, INET6_ADDRSTRLEN));
        }
        p = p->ai_next; 
    }
    freeaddrinfo(res);
}

