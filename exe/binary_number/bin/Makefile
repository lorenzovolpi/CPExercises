CC = g++
CFLAGS = -g -Wall -pedantic 
LDFLAGS = -lstdc++
SRCD = ../
REMOVABLE = $(filter-out Makefile,$(wildcard *))

VPATH = $(SRCD)

%: %.c
	$(CC) $(CFLAGS£) $< -o $@ $(LDFLAGS)

clean:
	rm -rfv $(REMOVABLE)
