#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

char welcome_message[290] = "We are going to play Knock Knock\nI will say \"Knock Knock!\"\nThen I want you to type in:\nWho's there?\nWhatever I say next you should repeat and append \" who?\"\nThen I will deliver the punch line! If you type in something\nwrong I will tell you what I was expecting. Do you want to play (y/n)?\n";

#define START_STATE 0
#define KNOCK_STATE 1
#define WHO_STATE 2
#define END_STATE 3
