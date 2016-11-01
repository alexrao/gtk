#!/bin/sh

CC := gcc
Cflag := `pkg-config --cflags --libs gtk+-2.0`

source := main.c
obj := main

all:
	$(CC) $(source) $(Cflag) -o $(obj)

clean:
	rm $(obj)
