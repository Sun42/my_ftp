/*
** serveur.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Thu Mar 12 17:37:17 2009 christophe sundas
** Last update Sun Mar 15 23:28:28 2009 christophe sundas
*/
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "serveur.h"

int	main(int ac, char **av)
{
  int	port;

  gl_cs = 0;
  signal(SIGKILL, my_kill);
  if (ac < 2)
    {
      printf(SERV_USAGE);
      exit(0);
    }
  else
    {
      port = atoi(av[1]);
      do_server(port);
    }
  return (0);
}

/*
** prepar socket
*/
void			do_server(int port)
{
  int			sock;
  struct protoent	*proto;
  struct sockaddr_in	sin;
  char			*servdir;
  char			buf[BUF_SIZE];
  
  if ((servdir  = getcwd(buf, BUF_SIZE)) == NULL)
    my_exit("Can't get working directory");
  if ((proto = getprotobyname("tcp")) == NULL)
    my_exit(ERROR_PROTO);
  if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    my_exit(ERROR_SOCKET);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
   if ((bind(sock, (struct sockaddr*)&sin, sizeof(sin))) == -1)
    my_exit(ERROR_BIND);
   if ((listen(sock, 42)) == -1)
     my_exit(ERROR_LISTEN);
   printf("Serveur my_ftp ready on fd %i\n", sock);
   while (1)
     manage_socket(sock, servdir);
  if (close(sock) == -1)
    printf("Error closing socket sock %i \n", sock);
}

/*
** accepte un client, fork et execute la commande
*/
void			manage_socket(int sock, char *servdir)
{
  int			cs;
  struct sockaddr_in	client_sin;
  unsigned int		client_sin_len;
  int			child;
  
  client_sin_len = sizeof(client_sin);
  if ((cs = accept(sock, (struct sockaddr *)&client_sin, &client_sin_len)) == -1)
    {
      printf("%s on socket %i\n", ERROR_ACCEPT, sock);
      return ;
    }
  printf("connection from %s %i \n", inet_ntoa(client_sin.sin_addr), ntohs(client_sin.sin_port));
  child = fork();
  if (child < 0)
    printf("Erreur fork \n");
  if (child == 0)
    return ;
  else 
    do_child(cs, servdir);
}

void	do_child(int cs, char *servdir)
{
  int	nblu;
  char	buf[BUF_SIZE];

  gl_cs = cs;
  while (1)
    {
      nblu = recv(cs, buf, BUF_SIZE, 0);
      if (exec_cmd(buf, nblu, cs, servdir) == -1)
	break ;
      bzero(buf, BUF_SIZE);
    }
  close_client(cs);
}

int	my_kill(int sig)
{
  sig = sig;
  kill(0, SIGKILL);
  if (gl_cs)
    my_close(gl_cs);
  return (0);
}
