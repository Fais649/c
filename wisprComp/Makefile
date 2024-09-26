# Makefile

CC = gcc
WAYLAND_SCANNER = wayland-scanner

CFLAGS = -Wall -Wextra -DWLR_USE_UNSTABLE -I. $(shell pkg-config --cflags wlroots wayland-server xkbcommon)
LDFLAGS = $(shell pkg-config --libs wlroots wayland-server xkbcommon)

TARGET = compositor
SRCS = main.c xdg-shell-protocol.c
HEADERS = xdg-shell-protocol.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LDFLAGS)

xdg-shell-protocol.c xdg-shell-protocol.h: xdg-shell-protocol.xml
	$(WAYLAND_SCANNER) private-code xdg-shell-protocol.xml xdg-shell-protocol.c
	$(WAYLAND_SCANNER) client-header xdg-shell-protocol.xml xdg-shell-protocol.h

clean:
	rm -f $(TARGET) xdg-shell-protocol.c xdg-shell-protocol.h
