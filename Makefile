# COMPILE LINUX EXECUTABLE

CC = gcc
CFLAGS = -Wall -std=c99 -Iheaders
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
SRC = $(wildcard source_files/*.c)

all: clean main

main: 
	$(CC) $(CFLAGS) $(SRC) -o main $(LIBS)

clean:
	rm -f main

# # COMPILE WINDOWS EXE

# CC = x86_64-w64-mingw32-gcc
# CFLAGS = -Wall -Wextra -std=c99 -I/mnt/c/raylib/raylib/src -Iheaders
# LDFLAGS = -L/mnt/c/raylib/raylib/src -static -lraylib -lopengl32 -lgdi32 -lwinmm
# TARGET = pong.exe
# SRCS = $(wildcard source_files/*.c)
# OBJS = $(patsubst source_files/%.c, build/%.o, $(SRCS))

# all : $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# build/%.o: source_files/%.c
# 	@mkdir -p build
# 	$(CC) $(CFLAGS) -c $< -o $@

# # %.o: %.c
# # 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS) $(TARGET)
