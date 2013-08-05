CFLAGS := -L ../ -I ../ -std=c99
ifneq ($(SELECTIVE), )
 CFLAGS += -DSELECTIVE
endif

ifneq ($(PROFILE), )
 CFLAGS += -DPROFILE
endif

ifneq ($(PROFILE_NOSEL), )
 CFLAGS += -DPROFILE_NOSEL
endif

LIBS := -lcustomperf -lm
CC := gcc
LD_LIBRARY_PATH := ../


sample: sample.c
	$(CC) sample.c -o sample $(CFLAGS) $(LIBS) 

clean:
	$(RM) *.o sample
