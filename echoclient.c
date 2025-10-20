/*
 * echoclient.c - An echo client
 */
/* $begin echoclientmain */
#include "csapp.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;
    struct sockaddr_in serveraddr;
    socklen_t serverlen;
    char server_ip[INET_ADDRSTRLEN];

    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    /* Get server IP address */
    serverlen = sizeof(serveraddr);
    getpeername(clientfd, (struct sockaddr *)&serveraddr, &serverlen);
    inet_ntop(AF_INET, &serveraddr.sin_addr, server_ip, INET_ADDRSTRLEN);
    printf("Connected to server %s\n", server_ip);

    while (1) {
	printf("$ ");
	fflush(stdout);
	if (Fgets(buf, MAXLINE, stdin) == NULL)
	    break;
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	Fputs(buf, stdout);
    }
    Close(clientfd);
    exit(0);
}
/* $end echoclientmain */
