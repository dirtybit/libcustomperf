CFLAGS := -L ../ -I ../ -std=c99

ifneq ($(PROFILE), )
 CFLAGS += -DPROFILE
endif

LIBS := -lcustomperf -lm
CC := gcc
LD_LIBRARY_PATH := ../

all: sample delta profile

sample: sample.c
	$(CC) sample.c -o sample $(CFLAGS) $(LIBS) 

delta: delta.c
	$(CC) delta.c -o delta $(CFLAGS) $(LIBS) 

profile: profile.c
	$(CC) profile.c -o profile $(CFLAGS) $(LIBS)

clean:
	$(RM) *.o sample delta profile
