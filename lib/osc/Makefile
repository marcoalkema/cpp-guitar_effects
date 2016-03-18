#####################################################################
#       (c) Copyright 2015, Hogeschool voor de Kunsten Utrecht
#                       Hilversum, the Netherlands
#####################################################################
#
# Description   : Makefile for osc server and client
#
# Author        : Marc_G
# E-mail        : marcg@dinkum.nl
#
####################################################################/

CC = g++ -g
CFLAGS = -Wall


all: osc_client osc_server
osc_client: osc_client.o
	$(CC) -o $@ $(CFLAGS) osc_client.o -llo

osc_server: osc_server.o osc.o
	$(CC) -o $@ $(CFLAGS) osc_server.o osc.o -llo


.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm +111 -type f`

