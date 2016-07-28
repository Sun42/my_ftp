/*
** serv_cmd.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:57:16 2009 christophe sundas
** Last update Sun Mar 15 23:42:11 2009 christophe sundas
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

int	exec_cmd(char buf[BUF_SIZE], int nblu, int cs, char *servdir)
{
  char	*cmd;
  int	nbcmd;
  
  nbcmd = choose_cmd(buf, nblu);
  cmd = xmalloc(sizeof(*cmd) * (nblu + 1));
  cmd = strncpy(cmd, buf, nblu);
  cmd[nblu] = '\0';
  if (nbcmd == 4)
    {
      printf("command quit received \n");
      return (-1);
    }
  if (nbcmd == 1)
    put_response(cs, exec_ls(cs, servdir));
  if (nbcmd == 2)
    put_response(cs, exec_pwd(cs, servdir));
  if (nbcmd == 3)
    put_response(cs, exec_cd(servdir, cmd));
  if (nbcmd == 5)
    put_response(cs, exec_put(cs, cmd));
  if (nbcmd == 6)
    put_response(cs, exec_get(cs, cmd));
  free(cmd);
  return (0);
}

int	choose_cmd(char buf[], int nblu)
{
  if (strncmp(buf, "ls", 2) == 0)
    return (1);
  if (strncmp(buf, "pwd", 3) == 0)
    return (2);
  if (strncmp(buf, "cd ", 3) == 0)
    return (3);
   if (strncmp(buf, "quit", nblu) == 0)
     return (4);
   if (strncmp(buf, "put ", 4) == 0)
     return (5);
   if (strncmp(buf, "get ", 4) == 0)
     return (6); 
   return (-1);
}

void	put_response(int cs, int res)
{
  if (res == -1)
    send(cs, "ERROR\n", strlen("ERROR\n"), MSG_DONTWAIT);
  else
    send(cs, "SUCCESS\n", strlen("SUCCESS\n"), MSG_DONTWAIT);
}
