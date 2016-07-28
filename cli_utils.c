/*
** cli_utils.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:56:51 2009 christophe sundas
** Last update Sun Mar 15 22:56:52 2009 christophe sundas
*/
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

void	my_exit(char *error)
{
  printf("%s \n", error);
  exit(EXIT_FAILURE);
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

void	putstr(char *str)
{
  write(1, str, strlen(str));
}

void	mksize(char size[], int isize)
{
  if (isize != 0)
    my_itoa(isize, size);
  else
    {
      size[0] = '0';
      size[1] = '\0';
    }
}
