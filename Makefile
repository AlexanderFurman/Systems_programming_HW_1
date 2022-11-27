CC=gcc
OBJS= RLEList.o tool/AsciiArtTool.o tool/main.o #c.o
EXEC=AsciiArtTool
NO_DEBUG= -DNDEBUG# -g #for debug
CFLAGS=-std=c99 -Wall -Werror -pedantic-errors
INCLUDE_FLAG = -I/home/mtm/public/2223a/ex1 -Itool
RLE_TARGET = $*.c
TOOL_TARGET = $tool/*.c

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) $(NO_DEBUG) $(OBJS) $(INCLUDE_FLAG) $(RLE_TARGET) $(TOOL_TARGET) -o $@

tool/main.o: tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(NO_DEBUG) $(INCLUDE_FLAG) $(CFLAGS) $(RLE_TARGET) $(TOOL_TARGET)
tool/AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(NO_DEBUG) $(INCLUDE_FLAG) $(CFLAGS) $(RLE_TARGET) $(TOOL_TARGET)
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(NO_DEBUG) $(INCLUDE_FLAG) $(CFLAGS) $(RLE_TARGET)

clean:
	rm -f $(OBJS) $(EXEC)
