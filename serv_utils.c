/*
** serv_utils.c for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Thu Mar 12 17:37:00 2009 christophe sundas
** Last update Sun Mar 15 14:54:05 2009 christophe sundas
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include "serveur.h"

char	*strdup(const char *s1);

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

char	*mk_relative_path(char *cwd, char *servdir)
{
  if (strlen(cwd) < strlen(servdir))
    return (NULL);
  if (strcmp(cwd, servdir) == 0)
    return (strdup("/"));
  cwd += strlen(servdir);
  return (strdup(cwd));
}

char	*my_wordcat(char *str1, char *str2)
{
  char	*ret;

  if (str1 == NULL)
    return (strdup(str2));
  else
    {
      if (str2 != NULL)
	{
	  ret = malloc(strlen(str1) + strlen(str2) + 1);
	  ret = strcpy(ret, str1);
	  ret = strcat(ret, str2);
	  free(str1);
	  return (ret);
	}
    }
  return (NULL);
}

void	close_client(int cs)
{
  if (close(cs) == -1)
    printf("Error closing socket cs %i\n", cs);
}

void	my_exit(char *error)
{
  printf("%s \n", error);
  exit(-1);
}

