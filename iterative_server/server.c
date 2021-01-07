#include <sys/socket.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

int main(int agrc, char *argv[]) {
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;

    if (getaddrinfo("0.0.0.0", "7999", &hints, &res) != 0)
        exit(1);

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock <= 0) {
        perror("failed to create socket");
        exit(2);
    }

    if(bind(sock, res->ai_addr, res->ai_addrlen) != 0) {
        perror("failed to bind");
        exit(3);
    }

    if(listen(sock, 1024) != 0) {
        perror("listen failed");
        exit(4);
    }

    accept(sock, (struct sockaddr*) NULL, NULL);
}
