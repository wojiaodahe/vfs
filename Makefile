
OBJS = block_dev.o char_dev.o ofs.o ramfs.o vfs.o ramdisk.o

all: $(OBJS)
	gcc $(OBJS) -o task.exe -Wall -g

%.o: %.c 
	gcc -c  -Wall -g -I . -I arm $< -o $@

clean:
	del *.o
	del task.exe