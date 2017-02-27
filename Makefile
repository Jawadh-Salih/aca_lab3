CC = gcc
CFLAGS = -I
matvec : util.c matvec.c
	$(CC) -o matvec util.c matvec.c
