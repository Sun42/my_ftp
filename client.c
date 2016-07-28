/*
** client.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:57:01 2009 christophe sundas
** Last update Sun Mar 15 22:57:02 2009 christophe sundas
*/
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "client.h"

int	main(int ac, char **av)
{
  if (ac < 3)
    my_exit(CLIENT_USAGE);
  do_connect(av[1], av[2]);
  return (0);
}

void	do_connect(char *ip, char *sport)
{
  int			port;
  int			s;
  struct sockaddr_in	sin;
  char			*prompt;
  
  prompt = "my_ftp";
  port = atoi(sport);
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    my_exit(ERROR_SOCKET);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if ((connect(s, (struct sockaddr *)&sin, sizeof (struct sockaddr_in))) == -1)
    my_exit(ERROR_CONNECT);
  while (1)
    {
      if (do_cli(&prompt, s) == -1)
	break ;
    }
  my_close(s);
}

/*
** parse et execute les cmd
*/
int		do_cli(char **prompt, int s)
{
  char		*msg;
  char		buf[BUFFER_SIZE];
    
  msg = get_prompt(*prompt);
  if (strcmp(msg, "prompt") == 0)
    {  
      *prompt = change_prompt(*prompt);
      free (msg);
      return (1);
    }
  if (!inner_cmd(msg))
    return (extern_cmd(msg, s, buf));
  free (msg);
  return (0);
}

int	extern_cmd(char *msg , int s, char buf[])
{
  if (send(s, msg, strlen(msg), MSG_DONTWAIT) == -1)
    {
      free(msg);
      return (0);
    }
  if (strcmp(msg , "quit") == 0)
    {
      free(msg);
      return (-1);
    }
  if (strncmp(msg, "cd ", 3) == 0)
    wait_msg(buf, s);
  if (strncmp(msg, "put ", 4) == 0)
    do_put(msg, buf, s);
  if ((strcmp(msg , "ls") == 0) || (strcmp(msg, "pwd") == 0))
    do_lspwd(msg, s);
  if (strncmp(msg, "get ", 4) == 0)
    do_get(msg, buf, s);
  free(msg);
  return (0);
}


int	inner_cmd(char *msg)
{
  if (strcmp(msg, "lls") == 0)
    {
      do_lls();
      return (1);
    }
  if (strcmp(msg, "lpwd") == 0)
    {
      do_lpwd();
      return (1);
    }
  if (strncmp(msg, "lcd ", 4) == 0)
    {
      do_lcd(msg + 4);
      return (1);
    }
  return (0);
}
