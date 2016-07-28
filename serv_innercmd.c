/*
** serv_innercmd.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:57:53 2009 christophe sundas
** Last update Sun Mar 15 22:57:54 2009 christophe sundas
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

int	exec_cd(char *servdir, char *cmd)
{
  if (strlen(cmd) < 4)
    return (-1);
  else
    cmd += 3;
  if (can_chdir(servdir, cmd))
    return (0);
  return (-1);
}

int	exec_pwd(int cs, char *servdir)
{
  char	*cwd;
  char	*msg;
  char	buf[BUF_SIZE];

  cwd = getcwd(buf, BUF_SIZE);
  if (cwd == NULL)
    {
      cwd = "Can't get working directory";
      send(cs, cwd, strlen(cwd), MSG_DONTWAIT);
    }
  else
    {
      msg = mk_relative_path(cwd, servdir);
      msg = my_wordcat(msg, "\n");
      send(cs, msg, strlen(msg), MSG_DONTWAIT);
      if (msg != NULL)
        free(msg);
    }
  return (1);
}

int		exec_ls(int cs, char *servdir)
{
  char		*msg;
  DIR		*rep;
  struct dirent	*dirp;

  servdir = servdir;
  msg = NULL;
  if ((rep = opendir(".")) == NULL)
    {
      send(cs, "Can't open .", strlen("Can't open ."), MSG_DONTWAIT);
      return (-1);
    }
  else
    {
      while ((dirp = readdir(rep)))
        {
          msg = my_wordcat(msg, dirp->d_name);
          msg = my_wordcat(msg, "\n");
        }
      closedir(rep);
    }
  send(cs, msg, strlen(msg), MSG_DONTWAIT);
  if (msg != NULL)
    free(msg);
  return (0);
}

int	can_chdir(char *servdir, char *cmd)
{
  char	*cwd;
  char	buf2[BUF_SIZE];
  char	buf[BUF_SIZE];
  char	*pcwd;

  if ((pcwd = getcwd(buf2, BUF_SIZE)) == NULL)
    return (0);
  if (chdir(cmd) == 0)
    {
      if ((cwd = getcwd(buf, BUF_SIZE)) == NULL)
        return (0);
      if (strncmp(servdir, cwd, strlen(servdir)) != 0)
        {
          if (chdir(pcwd) != 0)
            {
              exit(EXIT_FAILURE);
            }
          return (0);
        }
      return (1);
    }
  else
    return (0);
}
