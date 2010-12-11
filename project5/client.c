#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *msg) 
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) 
{
    int sockfd, portno, n;
    //serv_addr is the server address.
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char * tx_buffer;
    char * rx_buffer;

    tx_buffer = (char *)malloc(sizeof(char) * 512);
    rx_buffer = (char *)malloc(sizeof(char) * 512);

    if (argc < 3) 
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);

    //Creates a Socket called sockfd. Sockets allow communication between different machines.
    //The server creates a named socket and has clients connect to it.
    //A successful connection returns one file discriptor to the client and one to the server.
    //socket(int domain, int type, int protocol)
    //AF_INIT: IPv4 Internet protocol.
    //SOCK_STREAM: reliable, two-way connection-based byte streams.
    //0: standard protocol.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) 
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    //htons() converts our port number in host byte order to network byte order. 
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    //Send start condition
    n = write(sockfd, "START\n", 6);

    while(1)
    {
        //Receive
        bzero(rx_buffer, 512);
        n = read(sockfd, rx_buffer, 512);
        if (n < 0) error("ERROR reading from socket");
        if(strcmp(rx_buffer, "STOP\n") == 0)
        {
            fprintf(stdout, "Bye\n");
            close(sockfd);
            return 0;
        }
        fprintf(stdout, rx_buffer, 512);

        //Transmit
        bzero(tx_buffer, 512);
        fgets(tx_buffer, 511, stdin);
        n = write(sockfd, tx_buffer, strlen(tx_buffer));
        if (n < 0) error("ERROR writing to socket");
    }
    return 0;
}
