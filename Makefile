# 컴파일러 설정
CC = gcc

CFLAGS = -Iinclude

SRCDIR = src
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = cpu_simulator

# Default target
all: $(EXECUTABLE)

# Link
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)

# Run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

header_lines:
	@find . -name "*.h" -print0 | xargs -0 cat | wc -l


source_lines:
	@find . -name "*.c" -print0 | xargs -0 cat | wc -l 


lines: header_lines source_lines