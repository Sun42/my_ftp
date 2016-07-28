/*
** serv_utils3.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:58:21 2009 christophe sundas
** Last update Sun Mar 15 22:58:22 2009 christophe sundas
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
