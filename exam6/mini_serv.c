#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

typedef struct s_client
{
	int fd;
	int id;
	int new;
	struct s_client *next;
} 				t_c;

void fatal()
{
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	exit(1);
}

t_c* find_client(t_c** client_list, int fd)
{
	t_c* tmp;

	tmp = *client_list;
	while (tmp)
	{
		if (tmp->fd == fd)
			return tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

void send_message(t_c** client_list, int fd, char *message, fd_set *write)
{
	t_c *loop = *client_list;
	while (loop)
	{
		if (FD_ISSET(loop->fd, write) && loop->fd != fd)
		//pas de fatal ici
			send(loop->fd, message, strlen(message), 0);
		loop = loop->next;
	}
}

void remove_client(t_c** client_list, int fd, fd_set* master)
{
	t_c* tmp = *client_list;
	t_c* to_delete;
	
	if (tmp && tmp->fd == fd) // je suis le premier
	{
		*client_list = tmp->next;
		free(tmp);
	}
	else
	{
		while (tmp && tmp->next && tmp->next->fd != fd)
			tmp = tmp->next;
		to_delete = tmp->next;
		tmp->next = tmp->next->next;
		free(to_delete);
	}
	FD_CLR(fd, master); // on enleve ce fd du master
	close(fd); // on le close
}

void add_client(t_c** client_list, int server_fd, int id, fd_set *master, fd_set *write)
{
	int fd;
	socklen_t len;
	struct sockaddr_in cli; 
	char str[40];

	len = sizeof(cli);
	fd = accept(server_fd, (struct sockaddr *)&cli, &len);
	if (fd < 0) 
		//pas de f atal ici
		return;

	t_c* new_client;
	new_client = malloc(sizeof(t_c));
	if (new_client == NULL)
		fatal();
	new_client->fd = fd;
	new_client->id = id; 
	new_client->new = 1;
	new_client->next = NULL;

	t_c* tmp = *client_list;
	if (tmp == NULL)
		*client_list = new_client;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_client;
	}
	sprintf(str, "server: client %d just arrived\n", new_client->id);
	send_message(client_list, new_client->fd, str, write);
	FD_SET(new_client->fd, master); // on ajoute ce fd aux fd ecoutés
}

int get_max_fd(t_c** client_list, int server_fd)
{
	t_c* tmp = *client_list;
	int max = server_fd;

	while (tmp)
	{
		if (tmp->fd > max)
			max = tmp->fd;
		tmp = tmp->next;
	}
	return (max);
}

void manage_str(char *str, int client_fd, t_c** client_list, fd_set* write)
{
	char tmp[40]; // important que ces buffers soient plus grands que dans le main pour la string "client"
	char buf[40];

    bzero(&tmp, sizeof(tmp));
    bzero(&buf, sizeof(buf));

    int i = 0;
    int j = 0;
   
   	t_c* client = find_client(client_list, client_fd);

	while (str[i])
    {
        tmp[j] = str[i];
        j++;
        if (str[i] == '\n')
        {
			tmp[j+1] = '\0';
			if (client->new == 1)
            	sprintf(buf, "client %d: %s",client->id, tmp);
           	else if (client->new == 0)
            	sprintf(buf, "%s", tmp);
			send_message(client_list, client_fd, buf, write);
            j = 0;
			client->new = 1;
            bzero(&tmp, sizeof(tmp));
            bzero(&buf, sizeof(buf));
        }
        i++;
    }
	if (tmp[0] != '\0')
	{
		if (client->new == 1)
		{
			sprintf(buf, "client %d: %s", client->id, tmp);
			client->new = 0;
		}
		else
			sprintf(buf, "%s", tmp);
		send_message(client_list, client_fd, buf, write);
        bzero(&tmp, sizeof(tmp));
        bzero(&buf, sizeof(buf));
	}
	return;
}

void server_run(int server_fd)
{
	t_c* client_list = NULL;
	int id = 0; // keep track des clients
	int res;
	int i;

	char buf[21];
	bzero(buf, sizeof(buf));
	int bytes;
	bytes = 0;

	fd_set master; 
	fd_set read; 
	fd_set write;

	FD_ZERO(&master);
	FD_ZERO(&read);
	FD_ZERO(&write);

	FD_SET(server_fd, &master);

	while (1)
	{
		read = write = master;
		
		res = select(get_max_fd(&client_list, server_fd) + 1, &read, &write, NULL, NULL);
		if (res < 0)
			continue; // agit comme un break mais force le loop a continuer

		i = 0;
		while (i <= get_max_fd(&client_list, server_fd))
		{
			if (FD_ISSET(i, &read))
			{
				if (i == server_fd)
				{
					add_client(&client_list, server_fd, id, &master, &write);
					id++;
					break; 				}
				else
				{
					t_c* client = find_client(&client_list, i);
					bytes = recv(i, &buf, 20, MSG_DONTWAIT);
					if (bytes < 0)
						break;
					else if (bytes == 0)
					{
            			bzero(&buf, strlen(buf));
						sprintf(buf, "server: client %d just left\n", client->id);
						send_message(&client_list, client->fd, buf, &write);
						remove_client(&client_list, client->fd, &master);
            			bzero(&buf, sizeof(buf));
						break; 
					}
					else
					{
						buf[bytes] = '\0';
						manage_str(buf, client->fd, &client_list, &write);
    					bzero(&buf, strlen(buf));
					}
					bzero(buf, sizeof(buf));
				}
			}
			i++;
		}
	}
}

int server_init(uint16_t port)
{
	int sockfd;
	struct sockaddr_in servaddr; 

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0)
		fatal(); 
	
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port); 
  
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		fatal();
	
	if (listen(sockfd, 0) < 0) // pas de queue = 0
		fatal();
	
	return (sockfd);
}
	
int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}

	uint16_t port = atoi(av[1]);
	int socket = server_init(port);
	server_run(socket);
	close(socket);
	return (0);
}
