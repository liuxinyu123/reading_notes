//
// Created by Liu Yakun on 2018/1/23.
//
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

const int Size = 512;

void server_service(int fd);

int main(int argc, char *argv[]) {
    int listenfd, connfd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error\n");
        return -1;
    }
    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&servaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind error\n");
        return -1;
    }
    if (listen(listenfd, 5) == -1) {
        perror("listen error\n");
        return -1;
    }
    socklen_t len = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
    server_service(connfd);
    close(connfd);
    close(listenfd);
    return 0;
}

void server_service(int fd) {
    char receive_buffer[Size];
    int n = 0;
    while ((n = read(fd, receive_buffer, Size)) != 0) {
        write(fd, receive_buffer, n);
    }
}