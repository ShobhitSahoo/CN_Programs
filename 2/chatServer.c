// To implement a chat application of client-server communication using TCP/IP
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
    int listenfd, connfd, len, n, k;
    char message[1000];
    //This is our main socket variable
    struct sockaddr_in servaddr, cliaddr;
    len = sizeof(servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Define the port at which the server will listen for connections.
    servaddr.sin_port = htons(0);
    // This will create a new Socket and also return the identifier of the same socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (struct sockaddr *)&servaddr, len);
    getsockname(listenfd, (struct sockaddr *)&servaddr, &len);
    printf("Port for client=%ld\n", (long)ntohs(servaddr.sin_port));
    printf("Enter bye to end the chat");
    do
    {
        listen(listenfd, 5);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
        n = read(connfd, message, sizeof(message));
        message[n] = 0;
        printf("Server received the message=%s\n", message);
        printf("Enter the message for client:");
        scanf("%s", message);
        write(connfd, message, sizeof(message));
        k = strcmp(message, "Bye");
    } while (k != 0);
    close(listenfd);
    return 0;
}