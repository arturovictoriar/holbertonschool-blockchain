CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3 -c
OBJDIR = targets/

SRC0 = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c ec_save.c ec_load.c ec_sign.c ec_verify.c
OBJ0 = $(addprefix $(OBJDIR), $(SRC0:%.c=%.o))
NAME0 = libhblk_crypto.a

libhblk_crypto.a: hblk_crypto.h $(OBJDIR) $(OBJ0)
	ar rcs $(NAME0) $(OBJ0)

$(OBJDIR)%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
