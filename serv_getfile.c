/*
** serv_getfile.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:57:33 2009 christophe sundas
** Last update Sun Mar 15 23:25:42 2009 christophe sundas
*/
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "serveur.h"

int	get_data(int cs, char *filename, int size)
{
  int	cpt;
  char	*fic;
  char	buf[BUF_SIZE];
  int	fd;
  int	nblu;

  fic = xmalloc(size);
  cpt = 0;
  while (cpt < size)
    {
      nblu = recv(cs, buf, BUF_SIZE, 0);
      send(cs, "ack", strlen("ack"), 0);
      memmove((char *)(unsigned )fic + cpt, buf, nblu);
      cpt += nblu;
    }
  if ((fd = open(filename, O_CREAT | O_RDWR)) == -1)
    {
      printf("Can't open filename \n");
      send(cs, "ERROR", strlen("ERROR"), 0);
      return (-1);
    }
  write(fd, fic, size);
  close(fd);
  return (1);
}

char	*get_filename(int cs)
{
  char	*filename;
  int	nblu;
  char	buf2[BUF_SIZE];

  nblu = recv(cs, buf2, BUF_SIZE, 0);
  send(cs, "ack", strlen("ack"), 0);
  if (nblu == -1)
    return (NULL);
  if (strncmp(buf2, "ERROR", strlen("ERROR")) == 0)
    return (NULL);
  filename = xmalloc(nblu + 1);
  filename[nblu] = '\0';
  filename = strncpy(filename, buf2, nblu);
  return (filename);
}

int	get_filesize(int cs)
{
  int	nblu;
  int	nbbytes;
  char	buf[BUF_SIZE];
  char	*size;

  nblu = recv(cs, buf, BUF_SIZE, 0);
  send(cs, "ack", strlen("ack"), 0);
  if (nblu == -1)
    return (-1);
  if (strncmp(buf, "ERROR", strlen("ERROR")) == 0)
    return (-1);
  size = xmalloc(nblu + 1);
  size[nblu] = '\0';
  strncpy(size, buf, nblu);
  nbbytes = atoi(size);
  free(size);
  return (nbbytes);
}

int	exec_put(int cs, char *cmd)
{
  int	size;
  char	*filename;

  if (strlen(cmd) < 4)
    return (-1);
  if ((size = get_filesize(cs)) == -1)
    return (-1);
  if ((filename = get_filename(cs)) == NULL)
    return (-1);
  if (get_data(cs, filename, size) == -1)
    return (-1);
  free(filename);
  return (1);
}
