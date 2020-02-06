NAME=libftprintf.a

SRCS_PATH=./srcs/
SRCS_FILES=parser.c float_precision.c print_int.c print_float.c utils.c\
			int_length.c int_precision.c flags.c ft_printf.c handlers.c\
			print_str_pointer_percent.c str_precision.c validators.c\

SRCS=$(addprefix $(SRCS_PATH), $(SRCS_FILES))

LIB_SRCS_PATH=./libft/
LIB_SRCS_FILES=ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c\
               		ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c\
               		ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c\
               		ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c\
               		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
               		ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c\
               		ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c\
               		ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
               		ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c\
               		ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c\
               		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c\
               		ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstaddend.c\
               		ft_lstfind.c ft_lstlen.c ft_memrealloc.c ft_memdup.c get_next_line.c

LIB_SRCS=$(addprefix $(LIB_SRCS_PATH), $(LIB_SRCS_FILES))

LIB_OBJECTS_PATH=./objs/
LIB_OBJECTS_FILES=$(LIB_SRCS_FILES:.c=.o)
LIB_OBJECTS=$(addprefix $(LIB_OBJECTS_PATH), $(LIB_OBJECTS_FILES))

OBJECTS_PATH=./objs/
OBJECTS_FILES=$(SRCS_FILES:.c=.o)
OBJECTS=$(addprefix $(OBJECTS_PATH), $(OBJECTS_FILES))

COMPILE=gcc -Wall -Wextra -Werror

INCLUDES=-I./includes -I./libs/libft
HEADERS_PATH=./includes/
HEADERS_FILES=ft_printf.h
HEADERS=$(addprefix $(HEADERS_PATH), $(HEADERS_FILES))

COLOR_RESET=\033[0m
COLOR_PENDING=\033[0;33m
COLOR_SUCCESS=\033[0;32m
COLOR_DEFAULT=\033[1;34m

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_OBJECTS) $(HEADERS)
	@echo "$(NAME)     [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@ar rc $(NAME) $(OBJECTS) $(LIB_OBJECTS) $(LIB)
	@ranlib $(NAME)
	@echo "\033[A\033[K\033[A"
	@echo "$(NAME)     [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"
	@echo "                  [$(COLOR_SUCCESS)FINISHED$(COLOR_RESET)]"

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@mkdir $(OBJECTS_PATH)types 2>/dev/null || echo "" > /dev/null
	@mkdir $(OBJECTS_PATH)utils 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -c $< -o $@

$(LIB_OBJECTS_PATH)%.o: $(LIB_SRCS_PATH)%.c
	@mkdir $(LIB_OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -c $< -o $@

clean:
	@rm -fv $(OBJECTS) > /dev/null
	@rm -rf $(OBJECTS_PATH) > /dev/null

fclean: clean
	@rm -fv $(NAME) > /dev/null

re: fclean all

.PHONY: clean fclean re all