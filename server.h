#ifndef SERVER_H
#define SERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>

typedef struct{
	int socket, fd_max, current_fd, clients_connected;
	fd_set master, read_fd;
	pthread_t thread;
} server;

server* server_init();
void server_delete(server *s);

int server_bind(server *s, const char *port);
int server_accept(server *s);
int server_listen(server *s, char *buffer);

int server_receive(server *s, int client_fd, char *buffer);

int server_send_client(server *s, int client_fd, char *data);
int server_send_all(server *s, char *data);






#endif
