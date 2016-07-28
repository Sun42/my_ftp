LIB = -lsocket -lnsl
#LIB = 
CC = /usr/sfw/bin/gcc
CFLAGS += -W -Wall -ansi -pedantic
NAME_SERV = serveur
SRC_SERV = server.c \
           serv_client.c \
           serv_listc.c \
           serv_listb.c \
           serv_connexion.c \
           serv_func.c \
           mylib.c

OBJ_SERV = $(SRC_SERV:.c=.o)

NAME_CLI = client
SRC_CLI = client.c \
	get_next_line.c \
	cli_utils.c \
	cli_utils2.c \
	cli_putfile.c \
	cli_cmd.c \
	cli_innercmd.c \
	cli_getfile.c

OBJ_CLI = $(SRC_CLI:.c=.o)
RM = rm -f

#Client
$(NAME_SERV) : $(OBJ_SERV)
	$(CC) -o $(NAME_SERV) $(OBJ_SERV) $(LIB)

re_serv : fclean_serv $(NAME_SERV)

clean_serv : 
	$(RM) $(OBJ_SERV)

fclean_serv : clean_serv 
	$(RM) $(NAME_SERV)

#Server
$(NAME_CLI) : $(OBJ_CLI)
		$(CC) -o $(NAME_CLI) $(OBJ_CLI) $(LIB)

re_cli : clean_cli $(NAME_CLI)

clean_cli : 
	$(RM) $(OBJ_CLI)

fclean_cli : clean_cli
	$(RM) $(NAME_CLI)

#ALL
fclean : fclean_serv fclean_cli

re : re_serv re_cli

all : $(NAME_SERV) $(NAME_CLI)
