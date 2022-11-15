EXEC=small_kvs
OBJDIR=./obj/

CC=gcc
LDFLAGS= -lm
CFLAGS=-Wall -Wimplicit-function-declaration

OBJ=small_kvs.o small_kvs_interface.o

OBJS= $(addprefix $(OBJDIR), $(OBJ))

all: obj $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.c
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj: 
	mkdir -p obj


clean:
	rm -rf $(OBJS) $(EXEC) $(OBJDIR)/*
	rm -rf tags
	rm -rf *.files
	rm -rf *.out
tags:
	ctags -R
cscope:
	find . \( -name '*.c' -o -name '*.h' \) -print > cscope.files
	cscope -i cscope.files
