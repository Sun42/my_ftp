/*
** cli_cmd.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar 15 22:56:01 2009 christophe sundas
** Last update Sun Mar 15 22:56:02 2009 christophe sundas
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
#include "get_next_line.h"

char	*get_prompt(char *prompt)
{
  putstr(prompt);
  putstr(" : ");
  return (get_next_line(1));
}

void	do_put(char *msg, char buf[], int s)
{
  send_file(s, msg);
  wait_msg(buf, s);
}

void	do_get(char *msg, char buf[], int s)
{
  get_file(s, msg);
  wait_msg(buf, s);
}

void	do_lspwd(char buf[], int s)
{
  wait_msg(buf, s);
  wait_msg(buf, s);
}


char	*change_prompt(char *oldprompt)
{
  char	*new_prompt;

  printf("Ancien prompt : %s \n", oldprompt);
  putstr("Nouveau prompt : ");
  new_prompt = get_next_line(1);
  printf("Message enregistre : %s\n", new_prompt);
  return (new_prompt);
}
