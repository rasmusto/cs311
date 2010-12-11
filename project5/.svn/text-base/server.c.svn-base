//Torben Rasmussen
//Yiwei Li
//Gabriel Condrea
/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "server.h"

//FILE * log;
int sockfd, newsockfd, portno, clilen;
struct sigaction original_act, new_act;
int state = NULL;
int x;

void catchint(int signo) 
{
    fprintf(stdout, "Caught an interrupt\n");
    close(sockfd);
    close(newsockfd);
    exit(1);
}

void catchchild(int signo)
{
    fprintf(stdout, "My kid #%d is done and waited for!\n", x);
}

void error(char *msg) 
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    char * tx_buffer;
    tx_buffer = (char *)malloc(sizeof(char) * 512);
    char * rx_buffer;
    rx_buffer = (char *)malloc(sizeof(char) * 512);

    //sockaddr_in is a struct containing an internet address.
    //serv_addr is the server address.
    //cli_addr is the client address.
    struct sockaddr_in serv_addr, cli_addr;
    char * subject[5];
    char * punchline[5];
    int n;

    char knock[14]= "Knock! Knock!\n";

    subject[0] = "Turnip\n";
    punchline[0] = "Turnip the heat, it's cold in here! Want another? (y/n)\n";

    subject[1] = "Little Old Lady\n";
    punchline[1] = "I didn't know you could yodel! Want another? (y/n)\n";

    subject[2] = "Atch\n";
    punchline[2] = "Bless you! Want another? (y/n)\n";

    subject[3] = "Who\n";
    punchline[3] = "Is there an owl in here? Want another? (y/n)\n";

    subject[4] = "Who\n";
    punchline[4] = "Is there an echo in here? Want another? (y/n)\n";

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

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
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    //htons() converts our port number in host byte order to network byte order. 
    serv_addr.sin_port = htons(portno);

    //Bind - bind a name to a socket.
    //bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    //When a socket is created with socket(), it has an address family, but no address assigned.
    //Bind simply assigns the address specified by 'addr'.
    //This if statements checks to see that it gets bound correctly.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    fprintf(stdout, "I am the Knock Knock server and my pid number is %d\n", getpid());

    //  *************Signal handling*************
    new_act.sa_handler = catchint;
    new_act.sa_flags = 0;
    sigaction(SIGINT, &new_act, &original_act);

    new_act.sa_handler = catchchild;
    new_act.sa_flags = 0;
    sigaction(SIGCHLD, &new_act, NULL);

    original_act.sa_handler = SIG_IGN;
    //  *****************************************

    //log = fopen(".log", "w");

    int i = 0;
    while(1)
    {

        //Listen for connections to a socket.
        //This accepts incoming connections requests by accept().
        //5 is the backlog, the maximum length of pending connections.
        //(ECONNFUSED) is the display error.
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        
        //Accepts a connection on a socket.
        //It first extracts the connection request on the queue,
        //creates a new connected socket, and returns a file discriptor
        //referring to that socket.
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        else
        {
            x = fork();
            //fprintf(stdout, "forking\n", 10);
            if(x > 0)
            {
                fprintf(stdout,"A connection! My kid #%d will take care of it!\n", x);
            }
        }
        if (n < 0) error("ERROR writing to socket");

        if (x == 0)
        { //Receive
            bzero(rx_buffer, 512);
            n = read(newsockfd,rx_buffer, 512);
            if (n < 0) error("ERROR reading from socket");
            //fprintf(stdout, "\tReceived %s\n", rx_buffer);

            if(strcmp(rx_buffer, "START\n") == 0)
            {
                n = write(newsockfd, welcome_message, strlen(welcome_message));
                state = START_STATE;
            }

            //fprintf(stdout, "ENTERING WHILE LOOP\n");
            while(1)
            {
                //fprintf(stdout, "STARTING WHILE LOOP\n");

                while(state == START_STATE)
                {
                    //fprintf(stdout, "entered start_state\n");
                    //Receive
                    bzero(rx_buffer, 512);
                    n = read(newsockfd,rx_buffer, 512);
                    if (n < 0) error("ERROR reading from socket");

                    //fprintf(stdout, "rx_buffer = %s\n", rx_buffer);

                    if(strcmp(rx_buffer, "y\n") == 0)
                    {
                        state = KNOCK_STATE;
                        //fprintf(stdout, "state changed to KNOCK\n");
                        n = write(newsockfd, knock, strlen(knock));
                    }
                    else if(strcmp(rx_buffer, "n\n") == 0)
                    {
                        n = write(newsockfd, "STOP\n", 5);
                        close(newsockfd);
                        fprintf(stdout, "Closing this connection\n");
                        return 0;
                    }
                    else
                    {
                        n = write(newsockfd, "Unknown command, please enter y or n\n", 512);
                        if (n < 0) error("ERROR writing to socket");
                    }
                }

                while(state == KNOCK_STATE)
                {
                    //fprintf(stdout, "entered knock_state\n");
                    //Receive
                    bzero(rx_buffer, 512);
                    n = read(newsockfd,rx_buffer, 512);
                    if (n < 0) error("ERROR reading from socket");

                    if(strcmp(rx_buffer, "Who's there?\n") == 0){
                        state = WHO_STATE;
                        n = write(newsockfd, subject[i], strlen(subject[i]));
                        //fprintf(stdout, "state changed to WHO\n");
                    } 
                    else
                    {
                        n = write(newsockfd, "You're supposed to say \"Who's there?\". Try again.\n", 512);
                        if (n < 0) error("ERROR writing to socket");
                    }
                }

                while(state == WHO_STATE)
                {
                    //fprintf(stdout, "entered who_state\n");
                    //Receive
                    bzero(rx_buffer, 512);
                    n = read(newsockfd,rx_buffer, 512);
                    if (n < 0) error("ERROR reading from socket");

                    //fprintf(stdout, "subject[%d] = %s\n", i, subject[i]);
                    char temp[512];
                    strcpy(temp, subject[i]); 
                    temp[strlen(temp) - 1] = '\0';
                    strcat(temp, " who?\n");
                    if(strcmp(rx_buffer, temp) == 0)
                    {
                        state = END_STATE;
                        n = write(newsockfd, punchline[i], strlen(punchline[i]));
                        //fprintf(stdout, "state changed to END\n");
                    }

                    else
                    {
                        //n = write(newsockfd, "You're supposed to say \"\". Try again.\n", 512);
                        char temp2[1024] = "You're supposed to say \"";
                        strncat(temp2, temp, strlen(temp) - 1);
                        strcat(temp2, "\". Try again.\n");
                        n = write(newsockfd, temp2, strlen(temp2));

                        if (n < 0) error("ERROR writing to socket");
                    }
                }

                while(state == END_STATE)
                {
                    //fprintf(stdout, "entered end_state\n");
                    //Receive
                    bzero(rx_buffer, 512);
                    n = read(newsockfd,rx_buffer, 512);
                    if (n < 0) error("ERROR reading from socket");

                    if(strcmp(rx_buffer, "y\n") == 0)
                    {
                        state = KNOCK_STATE;
                        //fprintf(stdout, "state changed to KNOCK\n");
                        n = write(newsockfd, knock, strlen(knock));
                        i++;
                        if(i > 4)
                            i = 0;
                    }
                    else if(strcmp(rx_buffer, "n\n") == 0)
                    {
                        n = write(newsockfd, "STOP\n", 5);
                        close(newsockfd);
                        fprintf(stdout, "Closing this connection\n");
                        return 0;
                    }
                    else
                    {
                        n = write(newsockfd, "Unknown command, please enter y or n\n", 512);
                        if (n < 0) error("ERROR writing to socket");
                    }
                }

                //fprintf(stderr, "RESTARTING THE WHILE LOOP\n", 20);
            }
        }
        waitpid(x, NULL, 0);
    }
    return 0; 
}
