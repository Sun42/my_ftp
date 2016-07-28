/*
** client.h for  in /u/all/sundas_c/cu/rendu/unix/projet/my_ftp
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Thu Mar 12 17:36:16 2009 christophe sundas
** Last update Sun Mar 15 13:08:55 2009 christophe sundas
*/
#ifndef __MY_CLIENT_H__
# define __MY_CLIENT_H__
#define CLIENT_USAGE "usage : <ip_serveur> <port> \n"
#define ERROR_SOCKET "Can't create socket"
#define ERROR_CONNECT "Can't connect"
#define BUFFER_SIZE 4096

void	do_connect(char *ip, char *sport);
int	do_cli(char **prompt, int s);
void	wait_msg(char buf[], int s);
int	inner_cmd(char *msg);
int	extern_cmd(char *msg , int s, char buf[]);

/*
** cli_utils.h
*/
void	my_itoa(int nbr, char *str);
void	my_revstr(char *str);
void	my_exit(char *error);
void	putstr(char *str);
void	mksize(char size[], int isize);

/*
** cli_putfile.c
*/
void	send_file(int s, char *msg);
int	send_data(int s, char *msg);
int	proto_data(int s, void *fic, int size);
int	send_filesize(int s, char *msg);
int	send_filename(int s, char *msg);
void	send_wack(char *msg, int s);
int	send_wack_error(int s);
void	my_munmap(void *fic, int size);
void	my_close(int fd);


/*
** cli_cmd
*/
char	*get_prompt(char *prompt);
void	do_put(char *msg, char buf[], int s);
void	do_get(char *msg, char buf[], int s);
void	do_lspwd(char buf[], int s);
char	*change_prompt(char *oldprompt);

/*
** cli_innercmd
*/
void	do_lls();
void	do_lpwd();
void	do_lcd(char *newpath);

/*
** cli_getfile
*/
void	get_file(int s, char *msg);
int	get_filesize(int s);
int	get_data(int s, char *filename, int size);
char	*get_filename(int s);
void	*xmalloc(size_t taille);

#endif /* __MY_CLIENT_H__*/
