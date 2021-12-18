ifndef VERBOSE
.SILENT:
endif

NAME = minishell

SRCS =	builtins/cd_updatepath.c\
		builtins/cd2.c\
		builtins/echo.c\
		builtins/error.c\
		builtins/export.c\
		builtins/pwd.c\
		builtins/export2.c\
		builtins/export2_sort.c\
		builtins/free_memo.c\
		builtins/libft.c\
		builtins/unset.c\
		builtins/unset2_finc.c\
		env/env.c\
		env/shlvl.c\
		env/sort.c\
		env/tools_for_env.c\
		execute/bin.c\
		execute/exit.c\
		execute/for_builtin.c\
		minishell1/minishell.c\
		minishell1/signals.c\
		minishell1/token.c\
		minishell1/init.c\
		minishell1/types.c\
		minishell1/tools_for_main.c\
		parse/free.c\
		parse/parse.c\
		parse/parse2.c\
		parse/quote.c\
		parse/work_with_sep.c\
		parse/tools_for_parse.c\
		parse/tools_for_parse2.c\

FUNCTIONS = 	libft/ft_isascii.c \
				libft/ft_atoi.c\
				libft/ft_atoilen.c \
				libft/ft_isalnum.c \
				libft/ft_isalpha.c \
				libft/ft_isdigit.c \
				libft/ft_isprint.c \
				libft/ft_tolower.c \
				libft/ft_toupper.c \
				libft/ft_strlen.c \
				libft/ft_strlcpy.c \
				libft/ft_strlcat.c \
				libft/ft_strnstr.c \
				libft/ft_strchr.c \
				libft/ft_strncmp.c \
				libft/ft_strrchr.c \
				libft/ft_memset.c \
				libft/ft_bzero.c	\
				libft/ft_memcpy.c \
				libft/ft_memchr.c \
				libft/ft_memcmp.c \
				libft/ft_memccpy.c \
				libft/ft_strdup.c \
				libft/ft_calloc.c \
				libft/ft_memmove.c \
				libft/ft_putchar_fd.c \
				libft/ft_putstr_fd.c	\
				libft/ft_putnbr_fd.c \
				libft/ft_substr.c \
				libft/ft_strjoin.c \
				libft/ft_strtrim.c \
				libft/ft_putendl_fd.c \
				libft/ft_itoa.c \
				libft/ft_strmapi.c \
				libft/ft_split.c \
				libft/ft_lstnew.c \
				libft/ft_lstsize.c \
				libft/ft_lstlast.c \
				libft/ft_lstadd_front.c \
				libft/ft_lstadd_back.c \
				libft/ft_lstiter.c \
				libft/ft_lstdelone.c \
				libft/ft_lstclear.c \
				libft/ft_lstmap.c \
				libft/ft_atoi.c\
				libft/get_next_line.c\
				libft/get_next_line_utils.c\
				libft/printf.c\
				libft/sources/flag_in_string2.c\
				libft/sources/flag_in_string1.c\
				libft/sources/flag_edit.c\
				libft/sources/flags_init.c\
				libft/sources/output_char.c\
				libft/sources/output_characters.c\
				libft/sources/output_id.c\
				libft/sources/output_p.c\
				libft/sources/output_percentage.c\
				libft/sources/output_sixteen.c\
				libft/sources/output_string.c\
				libft/sources/output.c\
				libft/sources/output_u.c\
				libft/sources/search_and_stringfl.c\
				libft/utoa_f.c\
				libft/ft_strcmp.c\
				libft/itoa_f.c\

LIBFT_HEADER = libft/libft.h

GET_NEXT_LINE_HEADER = libft/get_next_line.h

PRINTF_HEADER = libft/ft_printf.h

HEADERS = minishell.h $(LIBFT_HEADER) $(GET_NEXT_LINE_HEADER) $(PRINTF_HEADER)

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra -I.

OBJS = $(SRCS:.c=.o)

OBJS += $(FUNCTIONS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
		@echo "\033[0;32mCompiling minishell..."
		ar rcs minishell.a $(OBJS)
		gcc -Wall -Werror -Wextra minishell1/minishell.c minishell.a -o $(NAME)
		@echo "\033[0;32mDone..."

clean:
		@echo "\033[31mDelete object files and lib..."
		$(RM) $(OBJS)
		$(RM) minishell.a
		@echo "\033[31mLib and object files deleted..."

fclean: clean
		@echo "\033[31mDelete minishell..."
		$(RM) $(NAME)
		@echo "\033[31mMinishell deleted..."

re: fclean all

.PHONY: all re fclean clean
