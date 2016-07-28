/*
** serveur.h for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Thu Mar 12 17:37:23 2009 christophe sundas
** Last update Sun Mar 15 23:17:58 2009 christophe sundas
*/
#ifndef __MY_SERVER_H__
# define __MY_SERVER_H__

#include <stdlib.h>
#include <sys/types.h>
#define SERV_USAGE "usage : <port>"
#define ERROR_PROTO "Can't find tcp protocol"
#define ERROR_SOCKET "Can't create socket"
#define ERROR_BIND "Can't bind socked"
#define ERROR_LISTEN "Can't listen on this port"
#define ERROR_ACCEPT "Can't accept client"
#define BUF_SIZE 4096 * 2
int	gl_cs;
/*
** serveur.c
*/
int	my_kill(int sig);
void	close_client(int cs);
void	manage_socket(int sock, char *servdir);
void	do_server(int port);
void	do_child(int cs, char *servdir);

/*
**  serv_cmd.h
*/
int	choose_cmd(char buf[], int nblu);
void	put_response(int cs, int res);
int	exec_cmd(char buf[BUF_SIZE], int nblu, int cs, char *servdir);

/*
** serv_innercmd.c
*/
int	exec_ls(int cs, char *servdir);
int	can_chdir(char *servdir, char *cmd);
int	exec_cd(char *servdir, char *cmd);
int	exec_pwd(int cs, char *servdir);

/*
** serv_utils
*/
void	*xmalloc(size_t taille);
char	*my_wordcat(char *ligne, char *newstr);
char	*mk_relative_path(char *cwd, char *servdir);
void	my_exit(char *error);

/*
** serv_utils2.h
*/
void	wait_msg(char buf[], int cs);
void	send_wack(char *msg, int cs);
int	send_wack_error(int cs);
void	my_revstr(char *str);
void	my_itoa(int nbr, char *str);

/*
** serv_utils3.c
*/
void	mksize(char size[], int isize);
void	my_munmap(void *fic, int size);
void	my_close(int fd);
/*
** serv_getfile.c
*/
int	exec_put(int cs, char *cmd);
int	get_filesize(int cs);
char	*get_filename(int cs);
int	get_data(int cs, char *filename, int size);

/*
** serv_putfile.c
*/
int	exec_get(int cs, char *cmd);
int	send_filesize(int cs, char *msg);
int	proto_data(int cs, void *fic, int size);
int	send_data(int cs, char *msg);
int	send_filename(int cs, char *msg);


#endif /* __MY_SERVER_H__*/
