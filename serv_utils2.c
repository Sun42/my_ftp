/*
** serv_utils2.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:58:16 2009 christophe sundas
** Last update Sun Mar 15 22:58:17 2009 christophe sundas
*/
#include <fcntl.h>
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
#include <sys/mman.h>
#include <dirent.h>
#include "serveur.h"

void	wait_msg(char buf[], int cs)
{
  int	nblu;

  nblu = recv(cs, buf, BUF_SIZE, 0);
  if (nblu == -1)
    return ;
  if (write(1, buf, nblu) == -1)
    return ;
}

void	send_wack(char *msg, int cs)
{
  char	buf[BUF_SIZE];

  send(cs, msg, strlen(msg), 0);
  recv(cs, buf, BUF_SIZE, 0);
}

int	send_wack_error(int cs)
{
  send_wack("ERROR", cs);
  return (-1);
}

void	my_revstr(char *str)
{
  int	c;
  int	i;
  int	j;

  i = 0;
  j = strlen(str) - 1;
  while (i < j)
    {
      c = str[i];
      str[i] = str[j];
      str[j] = c;
      i = i + 1;
      j = j - 1;
    }
}

void	my_itoa(int nbr, char *str)
{
  int	i;
  int	signe;

  i = 0;
  signe = nbr;
  if (signe < 0)
    nbr = -nbr;
  while (nbr > 0)
    {
      str[i] = ((nbr % 10) + '0');
      nbr = nbr / 10;
      i = i + 1;
    }
  if (signe < 0)
    {
      str[i] = '-';
      i = i + 1;
    }
  str[i] = '\0';
  my_revstr(str);
}
