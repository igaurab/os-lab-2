/* $begin select */
#include "csapp.h"
void echo(int connfd);
void command(void);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    struct sockaddr_in *addr;
    char client_ip[INET_ADDRSTRLEN];
    fd_set read_set, ready_set;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    listenfd = Open_listenfd(argv[1]);  //line:conc:select:openlistenfd

    printf("Running server at %s | @igaurab\n", argv[1]);

    FD_ZERO(&read_set);              /* Clear read set */ //line:conc:select:clearreadset
    FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ //line:conc:select:addstdin
    FD_SET(listenfd, &read_set);     /* Add listenfd to read set */ //line:conc:select:addlistenfd

    while (1) {
	ready_set = read_set;
	Select(listenfd+1, &ready_set, NULL, NULL, NULL); //line:conc:select:select
	if (FD_ISSET(STDIN_FILENO, &ready_set)) //line:conc:select:stdinready
	    command(); /* Read command line from stdin */
	if (FD_ISSET(listenfd, &ready_set)) { //line:conc:select:listenfdready
            clientlen = sizeof(struct sockaddr_storage);
	    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	    /* Get and log client IP address */
	    addr = (struct sockaddr_in *)&clientaddr;
	    inet_ntop(AF_INET, &addr->sin_addr, client_ip, INET_ADDRSTRLEN);
	    printf("Client connected from %s on fd %d\n", client_ip, connfd);

	    echo(connfd); /* Echo client input until EOF */
	    Close(connfd);
	    printf("Client %s disconnected\n", client_ip);
	}
    }
}

void command(void) {
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
	exit(0); /* EOF */
    printf("%s", buf); /* Process the input command */
}
/* $end select */


