#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    int sockfd, l, len, n, k;
    long port;
    char message[1000];
    struct sockaddr_in cliaddr;
    len = sizeof(cliaddr);
    printf("Enter the port number you got from Server Side:");
    scanf("%ld", &port);
    do
    {
        cliaddr.sin_family = AF_INET;
        cliaddr.sin_addr.s_addr = inet_addr("127.0.1.1");
        cliaddr.sin_port = htons(port);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        connect(sockfd, (struct sockaddr *)&cliaddr, len);
        printf("Enter a string for server");
        scanf("%s", message);
        write(sockfd, message, sizeof(message));
        n = read(sockfd, message, sizeof(message));
        message[n] = 0;
        printf("Client received the message=%s\n", message);
        k = strcmp(message, "Bye");
    } while (k != 0);
    close(sockfd);
    return 0;
}