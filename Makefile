
# CC = gcc
# CFLAGS = -Wall -Werror -g

# OBJS = main.o isOdd.o
# TARGET = prog

# .PHONY: all clean

# all: $(TARGET)
# 	./$(TARGET)
# 	@$(MAKE) clean

# $(TARGET): $(OBJS)
# 	@$(CC) $(CFLAGS) -o $@ $^

# main.o: main.c isOdd.h
# 	@$(CC) $(CFLAGS) -c $<

# isOdd.o: isOdd.c isOdd.h
# 	@$(CC) $(CFLAGS) -c $<

# clean:
# 	rm -f $(OBJS) $(TARGET)


CC = gcc
CFLAGS = -Wall -Werror -g

OBJS = main.o isOdd.o
TARGET = prog

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c isOdd.h
	$(CC) $(CFLAGS) -c $<

isOdd.o: isOdd.c isOdd.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
