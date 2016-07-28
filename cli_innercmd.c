/*
** cli_innercmd.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:56:26 2009 christophe sundas
** Last update Sun Mar 15 23:01:10 2009 christophe sundas
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
#include <dirent.h>
#include "client.h"

void	do_lcd(char *newpath)
{
  if (chdir(newpath) == -1)
    putstr("ERROR can't change dir\n");
  else
    putstr("SUCCESS \n");
}

void		do_lls()
{
  DIR		*rep;
  struct dirent	*dirp;

  if ((rep = opendir(".")) == NULL)
    {
      putstr("ERROR can't open dir\n");
      return ;
    }
  else
    {
      while ((dirp = readdir(rep)))
        {
	  putstr(dirp->d_name);
          putstr("\n");
	}
      if (closedir(rep) == -1)
	write(2, "Can't close dir", strlen("Can't close dir"));
    }
  putstr("SUCCESS \n");
}

void	do_lpwd()
{
  char	*pwd;
  char	buf[BUFFER_SIZE];
  
  pwd = getwd(buf);
  if (pwd == NULL)
    {
      putstr("ERROR can't get pwd \n");
    }
  else 
    {
      putstr(pwd);
      putstr("\n");
      putstr("SUCCESS \n");
    }
}
