#!/bin/sh
CFLAG := `pkg-config --cflags --libs gtk+-3.0`

CC := gcc
SOURCE := main.c

all:
	 $(CC) -o main $(SOURCE) $(CFLAG) -o main

clean:
	rm main
