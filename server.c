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

//////////////////////////////////////// Account ////////////////////////////////////////
typedef struct node {
  	char username[20];
	char password[20];
	int status;
	struct node *next;
}node;

node *head = NULL;

void insert(char username[20], char password[20], int status){
	node *temp;
	temp=(node *)malloc(sizeof(node));
	strcpy(temp->username, username);
	strcpy(temp->password, password);
	temp->status = status;
	temp->next = head;
	head = temp;
}

node *find(char name[20]){
   node *current = head;
   if(head == NULL)
	{
      return NULL;
    }
   while(strcmp(current->username, name) != 0){
      if(current->next == NULL){
         return NULL;
      }else {
         current = current->next;
	
      }
   }      
   return current;
}

void printAll()
{
    node *temp;
    temp = head;
    while(temp)
    {
    	printf("%20s %20s %d",temp->username, temp->password, temp->status;
        printf("\n");
        temp=temp->next;
    }
    printf("\n");
}

void openFile(){
	node *acc;
	char *username;
	char *password;
	int status;
	username = (char *)malloc(20);
	password = (char *)malloc(20);
    FILE *fptr;
	if((fptr=fopen("account.txt","r+"))==NULL){
		printf("Not find%s\n","account.txt");
		return;
	}
	while(1){
		fscanf(fptr,"%s",username);
		fscanf(fptr,"%s",password);
		fscanf(fptr,"%d",&status);
		if(feof(fptr)) break;
		insert(username, password, status);
	}
	free(username); free(password);
	fclose(fptr);
}

void writeFile(){
	FILE *fptr;
	node *temp;
    temp = head;
    fptr=fopen("account.txt","w+");
    while(temp){
    	fprintf(fptr, "%s %s %d", temp->username, temp->password, temp->status);
    	fprintf(fptr, "\n");
    	temp=temp->next;
    }
    fclose(fptr);
}

void registerAccount(){
	char username[20];
	char password[20];
	char homepage[200];
	printf("---------Register\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	printf("Password: "); scanf("%s", password);
	printf("\n");
	
	if(find(username) != NULL){
	printf("Account existed!");	
	} 
	else{
		insert(username, password, 2);
		writeFile();
		printf("Successful registration. Activation required.\n");
	}
	printf("\n");
}

void activateAccount(){
    char username[20];
	char password[20];
    char temp[20];
    char activationCode[20] = "LTM121216";
    int count = 0;
    printf("---------Activate\n");
    printf("Type username: "); scanf("%s", username);
    printf("\n");
    node *acc = find(username);
    if(acc != NULL){
		if(acc->status == 0){
			printf("Account has been blocked!\n");
            printf("------------------------\n");
		}
        else if(acc->status == 1){
            printf("Account is already activated!\n");
            printf("------------------------\n");
        }
        else if(acc->status == 2){
            printf("Account is idle - need to be activated!\n");
            printf("Type password: "); scanf("%s", password);
            printf("\n");
            if (strcmp(acc->password,password) == 0){
			printf("Success!\n");
            while (count<6) {
            printf("Type activation code: "); scanf("%s", temp);
            printf("\n");
            if (strcmp(temp,activationCode) == 0) {
                acc->status = 1;
                printf("Successful activation.\n");
                printf("------------------------\n");
                writeFile();
                printAll();
                count = 6;
                }
                else { 
                    count++;
                    if (count == 5) {
                        printf("Wrong code! You have failed 5 times. This account is now blocked!\n");
                        printf("------------------------\n");
                        acc->status = 0;
                        writeFile();
                        printAll();
                        count++;
                        }  
                    else {
                        printf("Wrong code! Try again.\n");
                    }
			}   
            }
        }
        else {
                printf("Wrong password!");
                printf("------------------------\n");
            }
        }
    }
    else { 
            printf("Account doesn't exist!\n");
            printf("------------------------\n");
           }
}

node *login(){
    char username[20];
	char password[20];
	int  count = 0;
    printf("---------Login\n");
    printf("Type username: "); scanf("%s",username);
    printf("\n");
    node *acc = find(username);
    if (acc != NULL) {
        if (acc->status == 0) {
            printf("Account is blocked!");
            printf("------------------------\n");
            return NULL;
        }
        else if (acc->status == 2) {
            printf("Account needs to be activated!");
            printf("------------------------\n");
            return NULL;
        }
        else {
            while (count<4) {
                printf("Type password: "); scanf("%s",password);
                printf("\n");
                if (strcmp(acc->password,password) == 0) {
                    printf("Login succesfully.\n");
                    printf("------------------------\n");
                    return acc;
                }
                else {
                    count++;
                    if (count==3) {
                        printf("Wrong password! You have failed 3 times. This account is now blocked!\n");
                        printf("------------------------\n");
                        acc->status = 0;
                        writeFile();
                        return NULL;
                    }
                    else {
                        printf("Wrong password! Try again.\n");
                    }
                }
            }
        }
    }
    else {
        printf("Account doesn't exist!");
        printf("------------------------\n");
        return NULL;
    }
}

void search(){
	char username[20];
	printf("---------Search\n");
	printf("Type username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){
		printf("Username: %20s Status: %d\n", acc->username, acc->status);
        printf("------------------------\n");
	}
	else {
        printf("Account does not exist\n");
        printf("------------------------\n");
        }
}

node *signout(){
	char username[20];
	printf("---------Sign Out\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc == NULL){
		printf("Account does not exist\n");
		return NULL;
	}
	else return acc;
}

void sendMess(char *content, int sockfd, struct sockaddr *servaddr){
	int len, sendBytes;
	  
	len = sizeof(*servaddr);

	sendBytes = send(sockfd, content, strlen(content) +1, 0);

	if(sendBytes < 0){
		perror("Error: \n");
	}
	
}

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