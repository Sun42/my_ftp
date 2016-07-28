/*
** serv_putfile.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:58:02 2009 christophe sundas
** Last update Sun Mar 15 23:26:29 2009 christophe sundas
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

int	exec_get(int cs, char *cmd)
{
  if (strlen(cmd) <= 4)
    return (-1);
  cmd += 4;
  if (send_filesize(cs, cmd) == 1)
    if (send_filename(cs, cmd) == 1)
      return (send_data(cs, cmd));
  return (-1);
}

int		send_filesize(int cs, char *msg)
{
  struct stat	st;
  int		fd;
  char		size[16];

  if ((fd = open(msg, O_RDONLY)) == -1)
    return (send_wack_error(cs));
  if (fstat(fd, &st) == -1)
    {
      my_close(fd);
      return (send_wack_error(cs));
    }
  mksize(size, st.st_size);
  send_wack(size, cs);
  my_close(fd);
  return (1);
}

int	proto_data(int cs, void *fic, int size)
{
  int	cpt;
  char	buf[BUF_SIZE];
  int	to_send;

  cpt = 0;
  while (cpt < size)
    {
      if (cpt + BUF_SIZE > size)
        to_send = size - cpt;
      else
        to_send = BUF_SIZE;
      send(cs, (char *)((unsigned )fic + cpt), to_send, 0);
      recv(cs,buf, BUF_SIZE, 0);
      cpt += BUF_SIZE;
    }
  return (1);
}

int		send_data(int cs, char *msg)
{
  struct stat	st;
  int		fd;
  void		*fic;

  if ((fd = open(msg, O_RDONLY)) == -1)
    return (send_wack_error(cs));
  if (fstat(fd, &st) == -1)
    {
      my_close(fd);
      return (send_wack_error(cs));
    }
  if ((fic = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    return (send_wack_error(cs));
  if (proto_data(cs, fic, st.st_size) == -1)
    return (-1);
  my_munmap(fic, st.st_size);
  my_close(fd);
  return (1);
}

int	send_filename(int cs, char *msg)
{
  struct stat	st;
  int		fd;

  if ((fd = open(msg, O_RDONLY)) == -1)
    return (send_wack_error(cs));
  if (fstat(fd, &st) == -1)
    {
      my_close(fd);
      return (send_wack_error(cs));
    }
  send_wack(msg, cs);
  return (1);
}
