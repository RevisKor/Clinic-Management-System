# 1. Compiler and flags
CC     := gcc
CFLAGS := -Wall -Wextra -g -Iinclude

# 2. Directories
SRCDIR := src
OBJDIR := obj

# 3. Target output
TARGET := app

# 4. Source and object file discovery
# main.c plus every .c file under src/ (including nested folders)
SRCS := main.c $(shell find $(SRCDIR) -name '*.c' 2>/dev/null)
OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

# 5. Default rule
all: $(TARGET)

# 6. Link step
$(TARGET): $(OBJS)
	@echo "Linking executable: $(TARGET)"
	$(CC) $(CFLAGS) $^ -o $@

# 7. Compile step: mirrors src/ into obj/
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# 8. Clean rule
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean rebuild run

rebuild:
	make clean
	make

run:
	./app
