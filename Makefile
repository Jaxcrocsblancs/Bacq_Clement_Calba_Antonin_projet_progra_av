SYSCONF_LINK = gcc
CPPFLAGS     = `sdl-config --cflags` -std=c99 -Wall -Wextra -g
LDFLAGS      =
LIBS         =  `sdl-config --libs` -lm

DESTDIR = ./obj/Debug/
TARGET  = project

OBJECTS := $(addprefix $(DESTDIR),$(patsubst %.c,%.o,$(wildcard *.c)))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): $(DESTDIR)%.o: %.c
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

