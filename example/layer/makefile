#!/bin/sh
CFLAG := `pkg-config --cflags --libs gtk+-2.0`

CC := gcc
SOURCE := main.c print.c

all:
	 $(CC) -o main $(SOURCE) $(CFLAG) -o main

clean:
	rm main
