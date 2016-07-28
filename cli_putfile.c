/*
** cli_putfile.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:56:34 2009 christophe sundas
** Last update Sun Mar 15 23:21:47 2009 christophe sundas
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

int		send_filesize(int s, char *msg)
{
  struct stat	st;
  int		fd;
  char		size[16];
  
  if ((fd = open(msg, O_RDONLY)) == -1)
    return (send_wack_error(s));
  if (fstat(fd, &st) == -1)
    {
      printf("Error fstat \n");
      my_close(fd);
      return (send_wack_error(s));
    }
  mksize(size, st.st_size);
  send_wack(size, s);
  my_close(fd);
  return (1);
}

int	send_filename(int s, char *msg)
{
  struct stat	st;
  int		fd;

  if ((fd = open(msg, O_RDONLY)) == -1)
    return (send_wack_error(s));
  if (fstat(fd, &st) == -1)
    {
      my_close(fd);
      return (send_wack_error(s));
    }
  send_wack(msg, s);
  return (1);
}

int	proto_data(int s, void *fic, int size)
{
  int	cpt;
  char	buf[BUFFER_SIZE];
  int	to_send;

  putstr("Debut envoi data: \n");
  cpt = 0;
  while (cpt < size)
    {
      if (cpt + BUFFER_SIZE > size)
	to_send = size - cpt;
      else
        to_send = BUFFER_SIZE;
      send(s, (char *)((unsigned )fic + cpt), to_send, 0);
      recv(s,buf, BUFFER_SIZE, 0);
      cpt += BUFFER_SIZE;
    }
  putstr("Envoi termine \n");
  return (1);
}

int		send_data(int s, char *msg)
{
  struct stat	st;
  int		fd;
  void		*fic;
  
  if ((fd = open(msg, O_RDONLY)) == -1)
    return (send_wack_error(s));
  if (fstat(fd, &st) == -1)
    {
      my_close(fd);
      return (send_wack_error(s));
    }
  if ((fic = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    return (send_wack_error(s));
  if (proto_data(s, fic, st.st_size) == -1)
    return (-1);
  my_munmap(fic, st.st_size);
  my_close(fd);
  return (1);
}

/*
** englobe le protocole denvoi de fichier
*/
void	send_file(int s, char *msg)
{
  if (strlen(msg) >= 4)
    {
      msg += 4;
      if (send_filesize(s, msg) == 1)
        if (send_filename(s, msg) == 1)
          send_data(s, msg);
    }
}
