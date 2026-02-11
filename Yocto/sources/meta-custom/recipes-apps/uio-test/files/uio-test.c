#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define IP_SIZE             0x10000

volatile uint32_t read_reg(char* path, unsigned offset)
{
    int fd = open(path, O_RDONLY | O_SYNC);

    if (fd < 0)
    {
        perror("open failed");
        return 0;
    }

    void* mem_ptr = mmap(NULL, IP_SIZE, PROT_READ, MAP_SHARED, fd, 0);

    if (mem_ptr == MAP_FAILED)
    {
        perror("mmap failed");
        close(fd);
        return 0;
    }

    volatile uint32_t data = *((volatile uint32_t *)(mem_ptr + offset));

    if (munmap(mem_ptr, IP_SIZE))
    {
        perror("munmap failed");
        close(fd);
        return 0;
    }

    close(fd);

    return data;
}

void write_reg(char* path, unsigned offset, volatile uint32_t data)
{
    int fd = open(path, O_RDWR | O_SYNC);

    if (fd < 0)
    {
        perror("open failed");
        return;
    }

    void* mem_ptr = mmap(NULL, IP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (mem_ptr == MAP_FAILED)
    {
        perror("mmap failed");
        close(fd);
        return;
    }

    *((volatile uint32_t *)(mem_ptr + offset)) = data;

    if (munmap(mem_ptr, IP_SIZE))
    {
        perror("munmap failed");
        close(fd);
        return;
    }

    close(fd);
}


int main(int argc, char **argv)
{
    uint8_t base;

    if ((argc == 4) && !strcmp(argv[1], "read")) //uio-test read [LOC] [OFFSET]
    {

        //Check if offset is decimal or hex
        if (!(strstr(argv[3], "0x")) && !(strstr(argv[3], "0X")))
        {
            base = 10;
        }
        else
        {
            base = 16;
        }

        unsigned offset = (unsigned)(strtoul(argv[3], NULL, base));
        volatile uint32_t data = read_reg(argv[2], offset);
        
        printf("Value from %s = %lu (Decimal), 0x%08X (Hex)\n", argv[2], data, data);
    }
    else if ((argc == 5) && !strcmp(argv[1], "write")) //uio-test write [LOC] [OFFSET] [VALUE]
    {
        //Check if offset is decimal or hex
        if (!(strstr(argv[3], "0x")) && !(strstr(argv[3], "0X")))
        {
            base = 10;
        }
        else
        {
            base = 16;
        }

        unsigned offset = (unsigned)(strtoul(argv[3], NULL, base));

        //Check if value is decimal or hex
        if (!(strstr(argv[4], "0x")) && !(strstr(argv[4], "0X")))
        {
            base = 10;
        }
        else
        {
            base = 16;
        }

        volatile uint32_t value = strtoul(argv[4], NULL, base);

        write_reg(argv[2], offset, value);
        
        if (read_reg(argv[2], offset) != value)
        {
            printf("Failed to properly write %lu to %s (offset = %u)\n", value, argv[2], offset);
        }
        else
        {
            printf("Wrote %lu to %s (offset = %u)\n", value, argv[2], offset);
        }
    }
    else
    {
        printf("If you're trying to read from UIO, command needs to look like: uio-test read /dev/uio(X) [OFFSET]\n");
        printf("If you're trying to write to UIO, command needs to look like: uio-test write /dev/uio(X) [OFFSET] [VALUE]\n");
        return 1;
    }


    return 0;
}
