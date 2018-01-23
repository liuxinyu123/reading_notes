//
// Created by Liu Yakun on 2018/1/23.
//
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

const int Size = 512;

void client_service(FILE *fp, int fd);

int main(int argc, char *argv[]) {
    if (2 != argc) {
        fprintf(stderr, "usage : %s + ip\n", argv[0]);
        return -1;
    }
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error\n");
        return -1;
    }
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("connect error\n");
        return -1;
    }
    client_service(stdin, sockfd);
    close(sockfd);
    return 0;
}

void client_service(FILE *fp, int fd) {
    char send_buffer[Size], receive_buffer[Size];
    int n = 0;
    while (fgets(send_buffer, Size, fp)) {
        write(fd, send_buffer, Size);
        n = read(fd, receive_buffer, Size);
        receive_buffer[n] = 0;
        fputs(receive_buffer, stdout);
    }

}