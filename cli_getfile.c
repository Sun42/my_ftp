/*
** cli_getfile.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:56:16 2009 christophe sundas
** Last update Sun Mar 15 23:24:16 2009 christophe sundas
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

int     get_filesize(int s);
int     get_data(int s, char *filename, int size);
char    *get_filename(int s);
void	*xmalloc(size_t taille);

void	get_file(int s, char *msg)
{
  char	*filename;
  int	size;

  if (strlen(msg) < 4)
    return ;
  if ((size = get_filesize(s)) == -1)
    return ;
  if ((filename = get_filename(s)) == NULL)
    return ;
  if (get_data(s, filename, size) == -1)
    return ;
  free(filename);
}


int	get_filesize(int s)
{
  int	nblu;
  int	nbbytes;
  char	buf[BUFFER_SIZE];
  char	*size;

  nblu = recv(s, buf, BUFFER_SIZE, 0);
  send(s, "ack", strlen("ack"), 0);
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

void	*xmalloc(size_t taille)
{
  char	*malloced;

  if ((malloced = malloc(taille)) == NULL)
    {
      printf("Error malloc \n");
      exit(EXIT_FAILURE);
    }
  return (malloced);
}


char	*get_filename(int s)
{
  char	*filename;
  int	nblu;
  char	buf2[BUFFER_SIZE];

  nblu = recv(s, buf2, BUFFER_SIZE, 0);
  send(s, "ack", strlen("ack"), 0);
  if (nblu == -1)
    return (NULL);
  if (strncmp(buf2, "ERROR", strlen("ERROR")) == 0)
    return (NULL);
  filename = xmalloc(nblu + 1);
  filename[nblu] = '\0';
  filename = strncpy(filename, buf2, nblu);
  return (filename);
}

int	get_data(int s, char *filename, int size)
{
  int	cpt;
  char	*fic;
  char	buf[BUFFER_SIZE];
  int	fd;
  int	nblu;

  fic = xmalloc(size);
  cpt = 0;
  while (cpt < size)
    {
      nblu = recv(s, buf, BUFFER_SIZE, 0);
      send(s, "ack", strlen("ack"), 0);
      memmove((char *)(unsigned )fic + cpt, buf, nblu);
      cpt += nblu;
    }
  if ((fd = open(filename, O_CREAT | O_RDWR)) == -1)
    {
      printf("Can't open filename \n");
      send(s, "ERROR", strlen("ERROR"), 0);
      return (-1);
    }
  write(fd, fic, size);
  my_close(fd);
  return (1);
}
