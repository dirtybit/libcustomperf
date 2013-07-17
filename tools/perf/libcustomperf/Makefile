CFLAGS := -fPIC -O3 -g -Wall -Werror -Wextra -std=gnu99
CC := gcc
MAJOR := 0
MINOR := 1
NAME := customperf
VERSION := $(MAJOR).$(MINOR)

lib: lib$(NAME).so.$(VERSION)

lib$(NAME).so: lib$(NAME).so.$(VERSION)
	ldconfig -v -n .
	ln -s lib$(NAME).so.$(MAJOR) lib$(NAME).so

lib$(NAME).so.$(VERSION): lib$(NAME).o
	$(CC) -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@

install:
	rm /usr/local/lib/lib$(NAME).so.$(VERSION) /usr/local/lib/lib$(NAME).so.$(MAJOR) /usr/local/lib/lib$(NAME).so
	cp lib$(NAME).so.$(VERSION) /usr/local/lib/
	ln -s /usr/local/lib/lib$(NAME).so.$(VERSION) /usr/local/lib/lib$(NAME).so.$(MAJOR)
	ln -s /usr/local/lib/lib$(NAME).so.$(VERSION) /usr/local/lib/lib$(NAME).so
	ldconfig

clean:
	$(RM) *.o *.so*