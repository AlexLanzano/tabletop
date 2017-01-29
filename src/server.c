#include <server.h>


server* server_init()
{
	server *s = malloc(sizeof(server));
	s->socket = -1;
	FD_ZERO(&s->master);
	FD_ZERO(&s->read_fd);

	s->fd_max = 0;
	s->clients_connected = 0;
	
	return s;
}


void server_delete(server *s)
{
	close(s->socket);
}

int server_bind(server *s, const char *port)
{
	struct addrinfo addrConf;
	memset(&addrConf, 0, sizeof(addrConf));

	addrConf.ai_family = AF_UNSPEC;
	addrConf.ai_flags = AI_PASSIVE;
	addrConf.ai_socktype = SOCK_STREAM;
	addrConf.ai_protocol = IPPROTO_TCP;

	struct addrinfo *servAddr;

	if(getaddrinfo(NULL, port, &addrConf, &servAddr) != 0){
		return -1;
		  
	}

	for(struct addrinfo *addr = servAddr; addr != NULL; addr = addr->ai_next){
		s->socket = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);
		
		if(s->socket < 0){
			continue;
			
		}
		if((bind(s->socket, servAddr->ai_addr, servAddr->ai_addrlen) == 0) &&
		   (listen(s->socket, BACKLOG) == 0)){
			break;
			
		}
		close(s->socket);
		s->socket = -1;
		
	}
	
	if(s->socket < 0){
		return -1;
		
	}else{
		s->fd_max = s->socket;
		FD_SET(s->socket, &s->master);
		return 0;
		
	}
	
}
int server_accept(server *s)
{
	struct sockaddr_storage clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	int client_fd = accept(s->socket, (struct sockaddr *) &clientAddr, &clientAddrLen);
	if(client_fd < 0){
		return -1;
		  
	}
	++s->clients_connected;
	return client_fd;
	
}
int server_listen(server *s, char *buffer)
{
	struct timeval timeout;
	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;
	s->read_fd = s->master;
	if(select(s->fd_max+1, &s->read_fd, NULL, NULL, &timeout) == -1){
		return -1;
		
	}
	
	for(s->current_fd = 0; s->current_fd <= s->fd_max; ++s->current_fd){
		if(FD_ISSET(s->current_fd, &s->read_fd)){
			if(s->current_fd == s->socket){
				return 1; // new client connected
				
			}
			else{
				return 0; // client sent something
				      
			}
			
		}
		
	}
	
}

int server_receive(server *s, int client_fd, char *buffer)
{
	int numBytesRcvd;
	if(numBytesRcvd = recv(client_fd, buffer, 255, 0) <= 0){
		if(numBytesRcvd == 0){
			--s->clients_connected;
			return -2; // client disconnected
			    
		}
		else{
			return -1; // failed to recv
			    
		}
		  
	}
	return 0;
	
}

int server_send_client(server *s, int client_fd, const char *data)
{
	char msg[BUFFERMAX];
	memset(msg, 0, BUFFERMAX);
	strncpy(msg, data, BUFFERMAX-1);

	if(FD_ISSET(client_fd, &s->master)){
		if(client_fd != s->socket){
			if(send(client_fd, msg, strcspn(msg, "\0"), 0) == -1){
				return -1; // failed to send
				      
			}
			    
		}
		  
	}
	else{
		return -2; // client_fd doesn't exist
		  
	}
	return 0;
	
}
int server_send_all(server *s, char *data)
{
	for(int fd = 0; fd <= s->fd_max; ++fd)
		server_send_client(s, fd, data);
	return 0;
}
