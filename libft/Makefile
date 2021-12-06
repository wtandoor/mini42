NAME = libft.a

LIBFT_HEADER = libft.h

GET_NEXT_LINE_HEADER = get_next_line.h

PRINTF_HEADER = ft_printf.h

FUNCTIONS = 	ft_isascii.c \
				ft_atoilen.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strlen.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strnstr.c \
				ft_strchr.c \
				ft_strncmp.c \
				ft_strrchr.c \
				ft_memset.c \
				ft_bzero.c	\
				ft_memcpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memccpy.c \
				ft_strcmp.c\
				ft_strdup.c \
				ft_calloc.c \
				ft_memmove.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c	\
				ft_putnbr_fd.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_putendl_fd.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_split.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_front.c \
				ft_lstadd_back.c \
				ft_lstiter.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstmap.c \
				get_next_line.c\
				get_next_line_utils.c\
				printf.c\
				sources/flag_in_string2.c\
				sources/flag_in_string1.c\
				sources/flag_edit.c\
				sources/flags_init.c\
				sources/output_char.c\
				sources/output_characters.c\
				sources/output_id.c\
				sources/output_p.c\
				sources/output_percentage.c\
				sources/output_sixteen.c\
				sources/output_string.c\
				sources/output.c\
				sources/output_u.c\
				sources/search_and_stringfl.c\
				utoa_f.c\
				itoa_f.c\

OBJS += $(FUNCTIONS:.c=.o)

HEADER = $(GET_NEXT_LINE_HEADER) $(LIBFT_HEADER) $(PRINTF_HEADER)

CC = gcc

RM		=	rm -f

CFLAGS	=	-Wall -Werror -Wextra -I.

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
				ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME) 

.PHONY:		all	clean fclean re 
