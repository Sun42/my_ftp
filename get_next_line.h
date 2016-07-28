/*
** get_next_line.h for get next line in /u/all/sundas_c/cu/rendu/unix/projet/get_next_line
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Thu Nov 13 22:39:58 2008 christophe sundas
** Last update Tue Mar 10 03:36:30 2009 christophe sundas
*/
#ifndef __GET_NEXT_LINE_H__
#define __GET_NEXT_LINE_H__
#define BUFFSIZE 48

char	*my_charcat(char *ligne, char c);
char	*del_bckslshN(char *ligne);
char	*get_next_line(int fd);
int	my_strlen(char *c);
char	*my_strcpy(char *dest, char *src);
#endif
