CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = bin/neutron
SRC     = neutrontui.c

all: $(TARGET)

$(TARGET): $(SRC) | bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

bin:
	@mkdir -p bin

run: $(TARGET)
	sudo ./$(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) /usr/local/bin/neutron

uninstall:
	rm -f /usr/local/bin/neutron

clean:
	rm -rf bin

.PHONY: all run install uninstall clean