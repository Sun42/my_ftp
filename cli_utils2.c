/*
** cli_utils2.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:58:41 2009 christophe sundas
** Last update Sun Mar 15 22:58:41 2009 christophe sundas
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

void	send_wack(char *msg, int s)
{
  char	buf[BUFFER_SIZE];

  send(s, msg, strlen(msg), 0);
  recv(s, buf, BUFFER_SIZE, 0);
}

int	send_wack_error(int s)
{
  send_wack("ERROR", s);
  return (-1);
}

void	my_munmap(void *fic, int size)
{
  if (munmap(fic, size) == -1)
    if (printf("Error munmap \n") == -1)
      write(2, "Error printf ", strlen("Error printf "));
}

void	my_close(int fd)
{
  if (close(fd) == -1)
    if (printf("Error close \n") == -1)
      write(2, "Error printf ", strlen("Error printf "));
}

void	wait_msg(char buf[], int s)
{
  int	nblu;

  nblu = recv(s, buf, BUFFER_SIZE, 0);
  if (nblu == -1)
    return ;
  if (write(1, buf, nblu) == -1)
    return ;
}
