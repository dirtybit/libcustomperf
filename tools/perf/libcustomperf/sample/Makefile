CFLAGS := -O3 -L ../ -I ../
ifneq ($(SELECTIVE), )
 $(info Android)
 CFLAGS += -DSELECTIVE
endif

LIBS := -lcustomperf -lm
CC := gcc
LD_LIBRARY_PATH := ../


sample: sample.c
	$(CC) sample.c -o sample $(CFLAGS) $(LIBS) 

clean:
	$(RM) *.o sample
