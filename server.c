#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define MAXLINE 100
#define MAX_LISTEN_QUEUE 100

pid_t fork(void);

int main(int argc, char* argv[]){

    openFile();
	openFileScore();

	strScore = special_char_remplace();
	strInstr = special_char_remplace1();
	

	pid_t pid;
    int listenfd, connfd, n, portNumber;
    pid_t childpid;
    socklen_t clilen;
    char buff[MAXLINE];
    struct sockaddr_in cliaddr, servaddr;

    portNumber = atoi(argv[1]);


    // construct socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // bind socket to ip address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portNumber);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, MAX_LISTEN_QUEUE);
    printf("%s\n", "Server running...waiting for connections.");

    node *acc;
	int option = 0, regis = 0, login = 0, numAns = 0, num = 0;
	
    // communicate with client
    while(1){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
        printf("%s\n", "Received request...");

		if( (pid = fork()) == 0) {           //process in child (forking)
			
			close(listenfd); 	             // child closes listening socket
			
			while(n = recv(connfd, buff, MAXLINE, 0) > 0){

        	}

			exit(0);			
		
		}

        if(n < 0){
            perror("Read error: ");
            exit(-1);
        }

        close(connfd);
    }

    close(listenfd);

    return 0;
}