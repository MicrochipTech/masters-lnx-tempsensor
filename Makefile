CC := $(CROSS_COMPILE)gcc
CFLAGS := -fPIC -Wall
NAME := tempsensor
MAJOR := 1
MINOR := 0
VERSION := $(MAJOR).$(MINOR)

.PHONY: all
all: lib$(NAME).so $(NAME)

lib: lib$(NAME).so.$(VERSION)

$(NAME): lib$(NAME).so
	$(CC) $(NAME).c -o $@ -L. -l$(NAME)
	
lib$(NAME).so: lib$(NAME).so.$(VERSION)
	@ln -sf lib$(NAME).so.$(VERSION) lib$(NAME).so.$(MAJOR)
	@ln -sf lib$(NAME).so.$(MAJOR) lib$(NAME).so
	
lib$(NAME).so.$(VERSION): lib$(NAME).o
	$(CC) -shared -Wl,-soname,lib$(NAME).so.$(VERSION) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.so* $(NAME)