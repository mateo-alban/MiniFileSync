CC=gcc

CFLAGS=-Isrc -pthread


SRC=src/main.c \
    src/scanner.c \
    src/copy.c \
    src/worker.c \
    src/process.c \
    src/monitor.c \
    src/shared.c \
    src/stats.c \
    src/logger.c \
    src/daemon.c \
    src/pid.c \
    src/control.c


TARGET=MiniFileSync


all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)


clean:
	rm -f $(TARGET)


run:
	./$(TARGET)


stop:
	./$(TARGET) stop